#include "ShaderProgram.h"

#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const string &vertex_file, const string &fragment_file)
{
	m_vertex_shader_id = compile_shader(vertex_file, GL_VERTEX_SHADER);
	m_fragment_shader_id = compile_shader(fragment_file, GL_FRAGMENT_SHADER);
	GLCall(m_program_id = glCreateProgram());
	GLCall(glAttachShader(m_program_id, m_vertex_shader_id));
	GLCall(glAttachShader(m_program_id, m_fragment_shader_id));
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::link_program()
{
	GLCall(glLinkProgram(get_program_id()));
	GLCall(glValidateProgram(get_program_id()));
	check_errors(get_program_id());
}

int ShaderProgram::compile_shader(const string &filename, GLenum type)
{
	string src = read_shader_source(filename);
	const char *shader_source = src.c_str();

	GLCall(unsigned int shader_id = glCreateShader(type));
	GLCall(glShaderSource(shader_id, 1, &shader_source, NULL));
	GLCall(glCompileShader(shader_id));
	check_errors(shader_id, ShaderTypes::VERTEX);
	
	return shader_id;
}

string  ShaderProgram::read_shader_source(const string &filename)
{
	string shader_source;
	std::ifstream infile;

	infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		infile.open(filename);
		std::stringstream fs;
		fs << infile.rdbuf();
		infile.close();
		shader_source = fs.str();
	}
	catch (std::ifstream::failure e)
	{
		cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
	}

	return shader_source;
}

void ShaderProgram::bind_attribute(int attr, const string &var_name)
{
	GLCall(glBindAttribLocation(get_program_id(), attr, var_name.c_str()));
}

int ShaderProgram::get_uniform_location(const string &uniform_name)
{
	std::unordered_map <string, int> cache = get_cache();
	if (cache.find(uniform_name) != cache.end())
		return cache[uniform_name];

	GLCall(int location = glGetUniformLocation(get_program_id(), uniform_name.c_str()));
	if (location == -1)
		cout << "WARNING: Uniform '" << uniform_name << "' doesn't exist!" << endl;
	else
		cache[uniform_name] = location;
	
	return location;
}

void ShaderProgram::start()
{
	GLCall(glUseProgram(get_program_id()));
}

void ShaderProgram::stop()
{
	GLCall(glUseProgram(0));
}

void ShaderProgram::clean_up()
{
	stop();
	GLCall(glDetachShader(get_program_id(), get_vertex_shader_id()));
	GLCall(glDetachShader(get_program_id(), get_fragment_shader_id()));
	GLCall(glDeleteShader(get_vertex_shader_id()));
	GLCall(glDeleteShader(get_fragment_shader_id()));
	GLCall(glDeleteProgram(get_program_id()));
}

void ShaderProgram::check_errors(unsigned int id)
{
	int status;
	char infoLog[1024];

	GLCall(glGetProgramiv(id, GL_LINK_STATUS, &status));
	if (!status)
	{
		GLCall(glGetProgramInfoLog(id, 1024, NULL, infoLog));
		cerr << "ERROR::SHADER_LINKING_ERROR of type: PROGRAM" << '\n' << infoLog << '\n' << endl;
	}
}

void ShaderProgram::check_errors(unsigned int id, ShaderTypes type)
{
	int status;
	char infoLog[1024];

	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &status));
	if (!status)
	{
		GLCall(glGetShaderInfoLog(id, 1024, NULL, infoLog));
		cerr << get_error_string(type) << '\n' << infoLog << '\n' << endl;
	}
}

string ShaderProgram::get_error_string(ShaderTypes type)
{
	switch (type)
	{
	case ShaderTypes::VERTEX:
		return "ERROR::SHADER_COMPILATION_ERROR of type: VERTEX";
		break;

	case ShaderTypes::FRAGMENT:
		return "ERROR::SHADER_COMPILATION_ERROR of type: FRAGMENT";
		break;
	default:
		return "UNKNOW ERROR";
	}
}

void ShaderProgram::set_bool(int location, bool value) const
{
	GLCall(glUniform1i(location, (int)value));
}

void ShaderProgram::set_int(int location, int value) const
{
	GLCall(glUniform1i(location, value));
}

void ShaderProgram::set_float(int location, float value) const
{
	GLCall(glUniform1f(location, value));
}

void ShaderProgram::set_vec2(int location, const glm::vec2 &value) const
{
	GLCall(glUniform2fv(location, 1, &value[0]));
}

void ShaderProgram::set_vec2(int location, float x, float y) const
{
	GLCall(glUniform2f(location, x, y));
}

void ShaderProgram::set_vec3(int location, const glm::vec3 &value) const
{
	GLCall(glUniform3fv(location, 1, &value[0]));
}

void ShaderProgram::set_vec3(int location, float x, float y, float z) const
{
	GLCall(glUniform3f(location, x, y, z));
}

void ShaderProgram::set_vec4(int location, const glm::vec4 &value) const
{
	GLCall(glUniform4fv(location, 1, &value[0]));
}

void ShaderProgram::set_vec4(int location, float x, float y, float z, float w) const
{
	GLCall(glUniform4f(location, x, y, z, w));
}

void ShaderProgram::set_mat2(int location, const glm::mat2 &mat) const
{
	GLCall(glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]));
}

void ShaderProgram::set_mat3(int location, const glm::mat3 &mat) const
{
	GLCall(glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]));
}

void ShaderProgram::set_mat4(int location, const glm::mat4 &mat) const
{
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]));
}
