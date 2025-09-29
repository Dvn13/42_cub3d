#include "cub3d.h"

static int	count_words(const char *s, char c)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_count++;
		i++;
	}
	return (word_count);
}

static char	*extract_word(const char *s, int start, int end)
{
	char	*word;

	word = safe_malloc(end - start + 1);
	if (!word)
		return (NULL);
	string_copy(word, &s[start], end - start);
	word[end - start] = '\0';
	return (word);
}

char	**split_string(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;
	int		j;
	int		start;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = safe_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		result[j] = extract_word(s, start, i);
		if (!result[j])
		{
			free_string_array(result);
			return (NULL);
		}
		j++;
	}
	return (result);
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		safe_free(array[i]);
		i++;
	}
	safe_free(array);
}
