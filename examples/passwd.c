#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

#define M_TRIE_DEBUG
#include <m_trie.h>

struct user_info {
	unsigned int id;
	char* shell;
	time_t change;
};

static void
print_user_info(void* _ui)
{
	struct user_info* ui;

	ui = _ui;
	printf("uid = %u, shell = %s, change = %s",
	       ui->id,
	       ui->shell,
	       "not implemented");
}

int
main(void)
{
	struct m_trie trie;
	struct passwd* pwd;
	struct user_info* ui;

	m_trie_init(&trie, m_trie_hash_alphabet, M_TRIE_AUX_STORE_NONE);

	while ((pwd = getpwent()) != NULL) {
		ui = malloc(sizeof(struct user_info));
		ui->id = pwd->pw_uid;
		ui->shell = strdup(pwd->pw_shell);
		ui->change = pwd->pw_change;

		printf("Adding '%s'\n", pwd->pw_name);

		m_trie_set(&trie,
		           pwd->pw_name, strlen(pwd->pw_name),
		           M_TRIE_COPY_SHALLOW, M_TRIE_OVERWRITE_ALLOW,
		           ui, 1);
	}
	endpwent();

	m_trie_interactive_walk(&trie, print_user_info);

	return EXIT_SUCCESS;
}

