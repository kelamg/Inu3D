#pragma once

#include "Common.h"

#include <glm/glm.hpp>
#include <unordered_map>

enum class ShaderTypes {
	VERTEX, FRAGMENT
};

class ShaderProgram
{
private:
	unsigned int m_program_id;
	unsigned int m_vertex_shader_id;
	unsigned int m_fragment_shader_id;
	std::unordered_map<string, int> m_uniform_location_cache; // caching

	int compile_shader(const string &filename, GLenum type);
	string read_shader_source(const string &filename);

public:
	ShaderProgram(const string &vertex_file, const string &fragment_file);
	~ShaderProgram();

	void link_program();
	void start();
	void stop();
	void clean_up();
	void bind_attribute(int attr, const string &var_name);
	void check_errors(unsigned int shader_id); // link stage error checking
	void check_errors(unsigned int shader_id, ShaderTypes type); //	compile stage error checking
	int get_uniform_location(const string &uniform_name);

	static string get_error_string(ShaderTypes type);

	inline int get_program_id() const { return m_program_id; }
	inline int get_vertex_shader_id() const { return m_vertex_shader_id; }
	inline int get_fragment_shader_id() const { return m_fragment_shader_id; }
	inline std::unordered_map<string, int> get_cache() { return m_uniform_location_cache; }

	// utility uniform functions
	void set_bool(int location, bool value) const;
	void set_int(int location, int value) const;
	void set_float(int location, float value) const;
	void set_vec2(int location, const glm::vec2 &value) const;
	void set_vec2(int location, float x, float y) const;
	void set_vec3(int location, const glm::vec3 &value) const;
	void set_vec3(int location, float x, float y, float z) const;
	void set_vec4(int location, const glm::vec4 &value) const;
	void set_vec4(int location, float x, float y, float z, float w);
	void set_mat2(int location, const glm::mat2 &mat) const;
	void set_mat3(int location, const glm::mat3 &mat) const;
	void set_mat4(int location, const glm::mat4 &mat) const;
};

