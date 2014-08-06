/**************************************************************************
 *   window.cxx                                                           *
 *                                                                        *
 *   Tactical Nuclear Beaver                                              *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation, version 2.                             *
 *                                                                        *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    *
 *   General Public License for more details.                             *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA            *
 *   02110-1301, USA.                                                     *
 *                                                                        *
 **************************************************************************/

#include "window.h"

Window::Window() { 
	this->width = 1024;
	this->height = 768;
	physics_engine = new PhysicsEngine();

	// keep track of fps
	this->t0_value = glfwGetTime();
	this->fps_frame_count = 0;
	this->fps = 0;
	this->time_interval = 0.2;
}

int Window::create(int argc, char *argv[]) {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	// Initialize GLFW
	if(!glfwInit() ) {
		return -1;
	}

	//Open an OpenGL window
	window = glfwCreateWindow(width,height,"Tactical Nuclear Beaver",NULL,NULL);

	if(!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, &sprites);
	glfwSetKeyCallback(window, key_callback);

	// load in the sprites
	this->load_sprites();
	this->physics_engine->set_sprites(this->sprites);

	while (!glfwWindowShouldClose(window)) {
        /* Render here */
		draw_scene();

       	/* Swap front and back buffers */
		glfwSwapBuffers(window);
	
		/* Poll for and process events */
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();

	// Exit Program
	exit (EXIT_SUCCESS);
}

void Window::draw_canvas() {
	float ratio = width / (float) height;

	// Clear the screen
	glViewport(0, 0, width, height);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
 
	// Reset the matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, ratio);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void Window::draw_scene() {
	// Set the canvas
	this->draw_canvas();

	// settings
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CW);

	// and let's draw
	physics_engine->update_sprites();
	draw_sprites();
	glFlush();

	// finally write statistics to screen
	this->calculate_fps();
	this->write_statistics();
 }

void Window::write_text(uint _x, uint _y, std::string str, float fontsize, float r/*=0*/, float g/*=0*/, float b/*=0*/) {
	FTGLPixmapFont font("/usr/share/fonts/TTF/arial.ttf");
	font.FaceSize(fontsize);
	// hack to print black text
	glPixelTransferf(GL_RED_BIAS, r);
	glPixelTransferf(GL_GREEN_BIAS, g);
	glPixelTransferf(GL_BLUE_BIAS, b);
 	glRasterPos2f(_x, _y + fontsize);
	font.Render(str.c_str());
}

// exit the program when the ESC key is pressed
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	glfwSetWindowShouldClose(window, GL_TRUE);

	std::vector<Sprite*>* sprites = reinterpret_cast<std::vector<Sprite*>*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_SPACE) {
		//std::cout << "SPACE IS PRESSED" << std::endl;
		dynamic_cast<Player*>(sprites->at(0))->set_jumping(true);
	}

	if (key == GLFW_KEY_A) {
		//std::cout << "A IS PRESSED" << std::endl;
		dynamic_cast<Player*>(sprites->at(0))->set_running(true);
		dynamic_cast<Player*>(sprites->at(0))->set_running_direction(DIRECTION_LEFT);
	}

	if (key == GLFW_KEY_D) {
		//std::cout << "D IS PRESSED" << std::endl;
		dynamic_cast<Player*>(sprites->at(0))->set_running(true);
		dynamic_cast<Player*>(sprites->at(0))->set_running_direction(DIRECTION_RIGHT);
	}
}

// print all errors to standard error
void Window::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Window::draw_sprites() {
		for(uint i=0; i<this->sprites.size(); i++) {
			//Draw clockwise
	    glColor3f(1.0, 1.0, 1.0);
	    glBindTexture(GL_TEXTURE_2D, this->sprites[i]->get_texture());

	    int left = this->sprites[i]->get_x();
	    int right = this->sprites[i]->get_x() + this->sprites[i]->get_width();
	    int top = this->height - (this->sprites[i]->get_y() + this->sprites[i]->get_height());
	    int bottom = this->height - (this->sprites[i]->get_y());

	    glBegin(GL_QUADS);
	    glTexCoord2i(1,1); glVertex2i(right , top);
	    glTexCoord2i(1,0); glVertex2i(right , bottom);
	    glTexCoord2i(0,0); glVertex2i(left , bottom);
	    glTexCoord2i(0,1); glVertex2i(left , top);
	    glEnd();
		}
}

void Window::load_sprites() {
	glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glFrontFace(GL_CW);

  // load the main character
  this->sprites.push_back(new Player());

  // load the floor tiles
  for(uint i=0; i<25; i++) {
  	this->sprites.push_back(new Floor());
  	this->sprites.back()->set_position(i*this->sprites.back()->get_width(), 
  		0);
  }
}

void Window::write_statistics() {
	this->write_text(0,0,"[Testing] Tactical Nuclear Beaver", 12, -1, -1, -1);
	std::stringstream ss;
	ss << "[Framerate] " << this->fps;
	this->write_text(0, 12, ss.str(), 12, -1, -1, -1);
	ss.str("");
	ss << "[Player position] (" << this->sprites[0]->get_x() << "," <<
			this->sprites[0]->get_y() << ")";
	this->write_text(0, 24, ss.str(), 12, -1, -1, -1);
	ss.str("");
	ss << "[Player velocity] (" << this->sprites[0]->get_vx() << "," <<
			this->sprites[0]->get_vy() << ")";
	this->write_text(0, 36, ss.str(), 12, -1, -1, -1);
}

void Window::calculate_fps() {
	current_time = glfwGetTime();

	if ((this->current_time - this->t0_value) > this->time_interval) {
		this->fps = (double)this->fps_frame_count / (this->current_time - this->t0_value);
		this->fps_frame_count = 0;
		this->t0_value = glfwGetTime();
	}
	else {
		this->fps_frame_count++;
	}
}