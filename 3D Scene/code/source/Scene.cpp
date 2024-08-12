/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#include "../header/Scene.hpp"
#include "../header/Model.hpp"
#include "../header/Ship.hpp"
#include "../header/Camera.hpp"
#include "../header/Light.hpp"

namespace MScenary
{
	Scene::Scene(unsigned width, unsigned height)
		:
		color_buffer(width, height),
		rasterizer(color_buffer)
	{
		window = new sf::Window(sf::VideoMode(width, height), "PG - Practica 1 - Martin Perez", sf::Style::Titlebar | sf::Style::Close);

		window->setVerticalSyncEnabled(true);

		initialize_scene();
	}

	void Scene::run()
	{
		exit = false;

		do
		{
			process_input();

			update();
			render();

			window->display();
		} while (not exit);
	}

	void Scene::process_input()
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) exit = true;
		}
	}

	void Scene::update()
	{
		static float angle = 0.0f;
		angle += 0.005f;

		for each (auto node in entities)
		{
			if (node.first == "island")
			{
				node.second.get()->get_transform()->set_rotation(0, angle, 0);
			}

			node.second->update();
		}
	}

	void Scene::render()
	{
		rasterizer.clear();

		Camera& camera = dynamic_cast<Camera&>(*entities["camera"]);

        Matrix44 camera_view_matrix = camera.get_view_matrix();
        Matrix44 projection_matrix = camera.get_projection_matrix(); 

		Light& light = dynamic_cast<Light&>(*entities["light"]);

        light.apply_view_transform(camera_view_matrix);

		for each (auto node in entities)
		{
			node.second->render(projection_matrix, camera_view_matrix, light);
		}

		color_buffer.blit_to_window();
	}

	void Scene::initialize_scene()
	{
		auto camera = std::make_shared<Camera>(this, 20.f, 1.5f, 5.f, 0.1f, 0.005f);
        camera->get_transform()->set_position(0.f, -3.f, 0.f);
        camera->get_transform()->set_rotation(0.5f, 0.f, 0.f);
        
        add_node("camera", camera);

		auto light = std::make_shared<Light>(this, 4.f, 0.3f);
		light->get_transform()->set_position(0.f, 3.f, 0.f);

        add_node("light", light);

		auto island = std::make_shared<Model>(this, "../../assets/main_island.obj");
        island->get_transform()->set_position(0.f, 2.f, -7.f);
        island->get_transform()->set_scale(0.2f);

        add_node("island", island);

		auto ship = std::make_shared<Ship>(this, "../../assets/ship.obj", 0.5f, 0.01f);
        ship->get_transform()->set_transform_parent(island->get_transform());
        ship->get_transform()->set_position(6.f, 0.f, 6.f);

        add_node("ship", ship);

        auto cloud1 = std::make_shared<Model>(this, "../../assets/cloud.obj");
        cloud1->get_transform()->set_transform_parent(island->get_transform());
        cloud1->get_transform()->set_position(20.f, -7.f, 0.f);

        add_node("cloud1", cloud1);
       
        auto cloud2 = std::make_shared<Model>(this, "../../assets/cloud.obj");
        cloud2->get_transform()->set_transform_parent(island->get_transform());
        cloud2->get_transform()->set_position(-27.f, -1.f, 0.f);

        add_node("cloud2", cloud2);

	}
}