#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <m_trie.h>

struct user_info {
	char* shell;
	time_t change;
	unsigned int id;
	char padding[sizeof(unsigned int)];
};

static void
print_user_info(void* _ui)
{
	struct user_info* ui;

	ui = _ui;
	printf("uid = %u, shell = %s, change = %ld\n",
	       ui->id, ui->shell, ui->change);
}

int
main(void)
{
	m_trie trie;
	struct passwd* pwd;
	struct user_info* ui;
	char input[255];

	m_trie_init(&trie, m_trie_hash_alphabet, M_TRIE_OVERWRITE_ALLOW);

	while ((pwd = getpwent()) != NULL) {
		ui = malloc(sizeof(struct user_info));
		ui->id = pwd->pw_uid;
		ui->shell = strdup(pwd->pw_shell);
		ui->change = pwd->pw_change;

		printf("Adding '%s'\n", pwd->pw_name);

		m_trie_insert(&trie, pwd->pw_name, strlen(pwd->pw_name), ui);
	}
	endpwent();

	while (1) {
		memset(input, '\0', 255);
		scanf("%s", input);
		if (m_trie_search(&trie, input, strlen(input), (void**)&ui) == M_TRIE_OK)
			print_user_info(ui);
	}

	m_trie_free(&trie);

	return EXIT_SUCCESS;
}

