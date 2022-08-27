/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorette <amorette@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:38:19 by amorette          #+#    #+#             */
/*   Updated: 2022/08/27 18:21:33 by amorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *new_line(char *mount_string)
{
	char *new_line = NULL;
	int i;

	i = 0;
	while(mount_string[i] != '\n')
	{
		new_line[i] = mount_string[i];
		i++;	
	}
	return (new_line);
}

char *read_line(int fd, char *mount_string)
{
	char	*buffer;
	int		len_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(float));

	if(!buffer)
		return (NULL);

	while(!ft_strchr(buffer, '\n') && len_read != 0 )
	{
		//printf("ponto de controle 02\n");
		len_read = read(fd, buffer, BUFFER_SIZE);
		if(len_read == -1)
		{
			free(buffer);
			return(NULL);
		}
		buffer[len_read] = '\0';
		mount_string = ft_strjoin(buffer, "");
	}
	free(buffer);

	printf("%s\n", mount_string);
	return (mount_string);
}

char *get_next_line(int fd)
{
	char		*line;
	static char	*mount_string;

	if(fd < 0 && BUFFER_SIZE < 0)
		return (NULL);
	mount_string = read_line(fd, mount_string);
	line = new_line(mount_string);
	return (line);
}

int main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("file_test/test.txt", O_RDONLY);

	i = 1;
	// ler duas linhas
	while(i < 2){
		line = get_next_line(fd);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
}
//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
