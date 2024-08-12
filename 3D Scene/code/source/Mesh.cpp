/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../header/Mesh.hpp"
#include "../header/Light.hpp"
#include "../header/math.hpp"

namespace MScenary
{
	Mesh::Mesh(size_t number_of_vertices, aiMesh* mesh)
	{
		render_transformation = Matrix44(1);
		render_matrix_calculated = false;

		original_vertices.resize(number_of_vertices);
		original_normals.resize(number_of_vertices);

		//Get the vertices and normals of the models for later transformations.

		for (size_t index = 0; index < number_of_vertices; index++)
		{
			auto& vertex = mesh->mVertices[index];

			auto& normal = mesh->mNormals[index];

			//w = 1 for vertex
			original_vertices[index] = Vertex(vertex.x, -vertex.y, vertex.z, 1.f);

			//w = 0 for vectors
			original_normals[index] = Vector4f(normal.x, normal.y, normal.z, 0.f);
		}

		transformed_vertices.resize(number_of_vertices);
		display_vertices.resize(number_of_vertices);

		// Set the colors as semi-grey for all the vertices

		transformed_colors.resize(number_of_vertices);
		original_colors.resize(number_of_vertices);

		for (size_t index = 0; index < number_of_vertices; index++)
		{
			original_colors[index].set(0.5f, 0.5f, 0.5f);
		}

		// We generate the vertex indices

		size_t number_of_triangles = mesh->mNumFaces;

		original_indices.resize(number_of_triangles * 3);

		Index_Buffer::iterator indices_iterator = original_indices.begin();

		for (size_t index = 0; index < number_of_triangles; index++)
		{
			auto& face = mesh->mFaces[index];

			assert(face.mNumIndices == 3);

			// We set the indices to be 3 so that all the faces have 3 vertices

			auto indices = face.mIndices;

			*indices_iterator++ = int(indices[0]);
			*indices_iterator++ = int(indices[1]);
			*indices_iterator++ = int(indices[2]);
		}
	}

	void Mesh::render(Rasterizer< Color_Buffer >& rasterizer, const Matrix44& transform_matrix, const Matrix44& model_view_matrix, Light& light_source)
	{
		unsigned width = rasterizer.get_color_buffer().get_width();
		unsigned height = rasterizer.get_color_buffer().get_height();

		if (!render_matrix_calculated)
		{
			Matrix44 identity(1);
			Matrix44 scaling = scale(identity, float(width / 2), float(height / 2), 100000000.f);
			Matrix44 translation = translate(identity, Vector3f{ float(width / 2), float(height / 2), 0.f });
			render_transformation = translation * scaling;
			render_matrix_calculated = true;
		}

		for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
		{
			//Vertex transformations Local Coords -> Proyected Coords.

			Vertex& vertex = transformed_vertices[index] = transform_matrix * original_vertices[index];

			// Proyected coords mess up the w component so we have to divide evyrithing / w to set it to 1.

			float divisor = 1.f / vertex.w;

			vertex.x *= divisor;
			vertex.y *= divisor;
			vertex.z *= divisor;
			vertex.w = 1.f;

			display_vertices[index] = Point4i(render_transformation * vertex);

			//Lightning Calculations, updating the normals with the view matrix so they stay in camera coords. and then setting the colors to their new value based on the light.

			Point4f& transformed_normal = model_view_matrix * original_normals[index];

			float light_intensity = light_source.calculate_light_intensity(transformed_vertices[index], transformed_normal);

			float red = (float(original_colors[index].red()) * light_intensity) / 255.f;

			transformed_colors[index].set_red(red);
			transformed_colors[index].set_green((original_colors[index].green() * light_intensity) / 255.f);
			transformed_colors[index].set_blue((original_colors[index].blue() * light_intensity) / 255.f);
		}

		for (int* indices = original_indices.data(), *end = indices + original_indices.size(); indices < end; indices += 3)
		{
			if (is_frontface(transformed_vertices.data(), indices))
			{
				// Se the color of the polygon based on previous calculations

				rasterizer.set_color(transformed_colors[*indices]);

				Point4i clipped_vertices[10];

				unsigned clipped_vertices_count = clip_triangle(display_vertices.data(), indices, indices + 3, clipped_vertices, &width, &height);

				if (clipped_vertices_count >= 3)
				{
					// Fill the polygon.

					rasterizer.fill_convex_polygon_z_buffer(display_vertices.data(), indices, indices + 3);
				}
			}
		}
	}

	bool Mesh::is_frontface(const Vertex* const projected_vertices, const int* const indices)
	{
		const Vertex& v0 = projected_vertices[indices[0]];
		const Vertex& v1 = projected_vertices[indices[1]];
		const Vertex& v2 = projected_vertices[indices[2]];

		return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) < 0.f);
	}

	unsigned Mesh::clip_triangle(Point4i* vertices, const int* init, const int* end, Point4i* clipped_vertices, const unsigned* width, const unsigned* height)
	{
		unsigned int clipped_vertices_count = 0;

		for (const int* vertex = init; vertex < end; ++vertex)
		{
			// Get the position of the vertex
			unsigned x = vertices[*vertex].x;
			unsigned y = vertices[*vertex].y;

			// Inside the screen
			if ((x >= 0) && (x < *width) && (y >= 0) && (y < *height))
			{
				clipped_vertices[clipped_vertices_count] = vertices[*vertex];
				clipped_vertices_count++;
			}
		}

		// Return the number of vertices inside the screen
		return clipped_vertices_count;
	}
}