/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_shader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 13:46:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 02:30:39 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * Glues together all shaders to the shader program.
 * 
 * @param mlx The MLX instance.
 * @param shaders The array of shaders
 * @return Wether initilization was successful.
 */
bool	mlx_init_shaders(t_MLX *mlx, uint32_t *shaders)
{
	uint32_t	i;
	int			success;
	char		infolog[512];
	t_mlx_ctx	*context;

	i = 0;
	context = mlx->context;
	context->shaderprogram = glCreateProgram();
	if (!context->shaderprogram)
		return (false);
	while (shaders[i])
		glAttachShader(context->shaderprogram, shaders[i++]);
	glLinkProgram(context->shaderprogram);
	glGetProgramiv(context->shaderprogram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(context->shaderprogram, sizeof(infolog), \
		NULL, infolog);
		fprintf(stderr, "%s", infolog);
		return (false);
	}
	i = 0;
	while (shaders[i])
		glDeleteShader(shaders[i++]);
	return (true);
}

/**
 * Opens the shader file and compiles it.
 * 
 * @param Path File path to the shader.
 * @param Type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER or ...
 * @return uint32_t 
 */
bool	mlx_compile_shader(const char *Path, int32_t Type, uint32_t *out)
{
	int32_t		success;
	char		infolog[512];
	const char	*shader_source = mlx_readfile(Path);

	if (!shader_source)
		return (false);
	*out = glCreateShader(Type);
	if (!*out)
		return (false);
	glShaderSource(*out, 1, &shader_source, NULL);
	glCompileShader(*out);
	glGetShaderiv(*out, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*out, sizeof(infolog), NULL, infolog);
		fprintf(stderr, "%s", infolog);
		return (false);
	}
	return (true);
}

/*
	unsigned VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer
	(
		0,					// Location = 0
		3,					// Size of vertex attribute
		GL_FLOAT,			// Type of the data
		GL_FALSE,			// Normalize data?
		3 * sizeof(float),	// Stride
		(void*)0			// Offset
	);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	unsigned int shader;
	shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, shader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgram, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}
	glDeleteShader(shader);
	glDeleteShader(fragmentShader);

	glUseProgram(m_shaderProgram);
	glBindVertexArray(VAO);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
*/