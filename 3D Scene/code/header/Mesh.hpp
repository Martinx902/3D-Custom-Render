/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include "Rasterizer.hpp"
#include "Color_Buffer.hpp"

#include <cstdlib>
#include <vector>
#include <assimp/scene.h>

namespace MScenary
{
	using  std::vector;
	using argb::Rgb888;
	using argb::Color_Buffer;

	class Light;

	/**
	 * @brief Represents a mesh object.
	 *
	 * This class provides functionality to create and render mesh objects.
	 */
	class Mesh
	{
	private:

		// Type aliases for simplicity

		typedef Rgb888                Color;		 ///< Type alias for a 24 bit color.
		typedef Color_Buffer<Color>   Color_Buffer;  ///< Type alias for 24 bit color buffer.
		typedef Point4f               Vertex;		 ///< Type alias for vertex.
		typedef vector<Vertex>        Vertex_Buffer; ///< Type alias for vertex buffer.
		typedef vector<int>           Index_Buffer;	 ///< Type alias for index buffer.
		typedef vector<Color>         Vertex_Colors; ///< Type alias for vertex colors.

		vector<Point4f>     original_normals;		 ///< Original normals of the given mesh.
		Vertex_Buffer       original_vertices;		 ///< Original vertices of the given mesh.
		Index_Buffer        original_indices;		 ///< Original indices of the given mesh.
		Vertex_Colors       original_colors;		 ///< Original colors of the given mesh.
		Vertex_Colors       transformed_colors;		 ///< New colors of the mesh based with lightning operations applied.
		Vertex_Buffer       transformed_vertices;	 ///< New vertices positions in projection coordinates.
		vector<Point4i>     display_vertices;		 ///< New vertices positions in display coordinates.

		Matrix44 render_transformation; ///< Display transformation matrix.
		bool render_matrix_calculated; ///< Flag indicating whether render matrix is calculated so we only have to calculate it once.

	public:

		/**
		 * @brief Constructs a Mesh object, setting the original normal, vertices and indices of the mesh.
		 * As well as resizing the next buffers to use.
		 *
		 * @param number_of_vertices The number of vertices in the mesh.
		 * @param mesh Pointer to the mesh data using Assimp Loader.
		 */
		Mesh(size_t number_of_vertices, aiMesh* mesh);

		/**
		 * @brief Manages the transformation of the vertices from model coords to display coords as well as the lighning calculus for the colors.
		 * Then sends it to the rasterizer and draws it in the screen.
		 *
		 * @param rasterizer The rasterizer object for rendering.
		 * @param transform_matrix The transformation matrix.
		 * @param model_view_matrix The model-view matrix.
		 * @param light_source The light source for illumination.
		 */
		void render(Rasterizer<Color_Buffer>& rasterizer, const Matrix44& transform_matrix, const Matrix44& model_view_matrix, Light& light_source);

	private:

		/**
		 * @brief Checks if the triangle defined by the vertices is facing the camera, if so we render it.
		 *
		 * @param projected_vertices Pointer to the projected vertices.
		 * @param indices Pointer to the vertex indices.
		 * @return True if the triangle is front-facing, false otherwise.
		 */
		bool is_frontface(const Vertex* const projected_vertices, const int* const indices);

		/**
		 * @brief Decides if the triangle should be rendered or not based on the position of its vertices in relation with the width and height of the screen
		 * It just for debug purpouses, it should optimised by appliying the Sutherland-Hodgman algorith so it creates new polygons instead of just discarting
		 * the triangles that are outside of the screen.
		 *
		 * @param vertices Pointer to the vertices of the triangle.
		 * @param init Pointer to the start of the triangle indices.
		 * @param end Pointer to the end of the triangle indices.
		 * @param clipped_vertices Pointer to store the clipped vertices.
		 * @param width Pointer to the width of the screen.
		 * @param height Pointer to the height of the screen.
		 * @return The number of clipped vertices.
		 */
		unsigned clip_triangle(Point4i* vertices, const int* init, const int* end, Point4i* clipped_vertices, const unsigned* width, const unsigned* height);
	};
}