/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../header/Model.hpp"
#include "../header/Scene.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace MScenary
{
	Model::Model(Scene* given_scene, const char* mesh_file_path) : Node(given_scene)
	{
		initialize_model(mesh_file_path);
	}

	void Model::initialize_model(const char* mesh_file_path)
	{
		Assimp::Importer importer;

		//Load model from file

		auto model = importer.ReadFile
		(
			mesh_file_path,
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
		);

		//Set as many meshes as the model has

		if (model && model->mNumMeshes > 0)
		{
			for (size_t i = 0; i < model->mNumMeshes; i++)
			{
				std::shared_ptr<Mesh> mesh(new Mesh
				(
					model->mMeshes[i]->mNumVertices,
					model->mMeshes[i]
				));

				meshes.push_back(mesh);
			}
		}
	}

	void Model::render(const Matrix44& projection_matrix, const Matrix44& view_matrix, Light& light_source)
	{
		Matrix44 transform_matrix = get_transform()->get_transform_matrix();

		for each (auto mesh in meshes)
		{
			//Coord.Escena -> Coord.Camara -> Coord.Project

			mesh->render(scene->get_rasterizer(), projection_matrix * transform_matrix, view_matrix * transform_matrix, light_source);
		}
	}
}