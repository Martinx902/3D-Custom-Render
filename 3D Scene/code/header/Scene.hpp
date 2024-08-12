/**
  * @author    Martin Pérez Villabrille
  * @copyright Copyright (c) 2023+ Martin Pérez Villabrille.
  *            All rights reserved
  */

#pragma once

#include "Node.hpp"
#include "Rasterizer.hpp"
#include "math.hpp"
#include "Color_Buffer.hpp"

#include <SFML/Window.hpp>

#include <cstdlib>
#include <memory>
#include <string>
#include <map>

namespace MScenary
{
	using  std::vector;
	using argb::Rgb888;
	using argb::Color_Buffer;

	/**
	 * @brief A Scene on the proyect, it contains nodes that can be rendered or modify the scene in some way like lights or cameras.
	 *
	 */
	class Scene
	{
		typedef Rgb888                Color;		///< Alias for 24 bit color type.
		typedef Color_Buffer< Color > Color_Buffer; ///< Alias for 24 bitcolor buffer type.

		Color_Buffer               color_buffer;	///< Display Color buffer for rendering.
		Rasterizer< Color_Buffer > rasterizer;		///< Rasterizer for rendering.

		std::map<std::string, std::shared_ptr<Node>> entities;	///< List of nodes in the scene with a unique id to be updated and rendered in scene.

		sf::Window* window; ///< Pointer to the SFML window.

		bool exit = false; ///< Flag to indicate whether the scene should exit and terminate the window.

	public:

		/**
		* @brief Constructs a new Scene object, initializing the scene visuals and the buffers.
		*
		* @param width  The width of the window.
		* @param height The height of the window.
		*/
		Scene(unsigned width, unsigned height);

		/**
		 * @brief Gets a node from the scene by its ID.
		 *
		 * @param id The ID of the node.
		 * @return std::shared_ptr<Node> The node with the specified ID.
		 */
		std::shared_ptr<Node> get_node_by_id(std::string& id)
		{
			return entities[id];
		}

		/**
		* @brief Adds a node to the scene with a given id.
		*
		* @param id       The ID of the node.
		* @param new_node The node to add.
		*/
		void add_node(const std::string& id, std::shared_ptr<Node> new_node)
		{
			if (!entities[id])
				entities[id] = new_node;
		}

		/**
		 * @brief Executes a loop that mantains the scene running, first gets the inputs, then updates the nodes and finally renders them.
		 */
		void run();

		/**
		 * @brief Gets the height of the window.
		 *
		 * @return size_t The height of the window.
		 */
		size_t get_window_height()
		{
			return window->getSize().y;
		}

		/**
		 * @brief Gets the width of the window.
		 *
		 * @return size_t The width of the window.
		 */
		size_t get_window_width()
		{
			return window->getSize().x;
		}

		/**
		 * @brief Gets the rasterizer of the scene.
		 *
		 * @return Rasterizer<Color_Buffer>& Reference to the rasterizer.
		 */
		Rasterizer< Color_Buffer >& get_rasterizer()
		{
			return rasterizer;
		}

		/**
		 * @brief Gets the SFML window.
		 *
		 * @return sf::Window& Reference to the SFML window.
		 */
		sf::Window& get_window()
		{
			return *window;
		}

	private:

		/**
		 * @brief Processes input events to see if the user has closed the window.
		 */
		void process_input();

		/**
		 * @brief Updates all the nodes in the scene, normally this would take care of the movement of the objects.
		 */
		void update();

		/**
		 * @brief Renders all the nodes in the scene, passing along the light source and the camera matrix for calculations in the meshes.
		 */
		void render();

		/**
		 * @brief Creates all the nodes in the scene as well as setting their parameters like position, variables and rotation.
		 */
		void initialize_scene();

		/**
		 * @brief Stops the main loop and closes the window.
		 */
		void exit_scene()
		{
			exit = true;
		}
	};
}