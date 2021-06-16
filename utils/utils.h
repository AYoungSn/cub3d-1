/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahnys <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:28:37 by ahnys             #+#    #+#             */
/*   Updated: 2021/04/07 20:06:23 by ahnys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int					ft_strcmp(char *s1, char *s2);
int					ft_strlen(char *s);
int					ft_endcmp(char *str, char *s);
t_list				*lst_add_back(t_list **list, char *line);
int					lst_clear(t_list **lst);
t_list				*ft_lstlast(t_list *lst);
int					is_space(char ch);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				*ft_strrchr(char *s, int c);
void				ft_swap(int *n1, int *n2);
long long			ft_abs(int n);
int					ft_intlen(int n);
char				*ft_itoa(int n);
void				screen_size(void *mlx, int *height, int *width);

#endif
