RONN=ronn
RFLAGS=--roff --warnings --organization=lovasko --manual=m_trie

.PHONY: clean all

all:                      \
	man/m_trie_init.3       \
	man/m_trie_free.3       \
	man/m_trie_insert.3     \
	man/m_trie_search.3     \
	man/m_trie_remove.3     \
	man/m_trie_remove_all.3 \
	man/m_trie_trim.3       \
	man/m_trie_hash.3       \


man/m_trie_init.3: src/init.md
	$(RONN) $(RFLAGS) src/init.md --pipe > man/m_trie_init.3

man/m_trie_free.3: src/free.md
	$(RONN) $(RFLAGS) src/free.md --pipe > man/m_trie_free.3

man/m_trie_insert.3: src/insert.md
	$(RONN) $(RFLAGS) src/insert.md --pipe > man/m_trie_insert.3

man/m_trie_search.3: src/search.md
	$(RONN) $(RFLAGS) src/search.md --pipe > man/m_trie_search.3

man/m_trie_remove.3: src/remove.md
	$(RONN) $(RFLAGS) src/remove.md --pipe > man/m_trie_remove.3

man/m_trie_remove_all.3: src/remove_all.md
	$(RONN) $(RFLAGS) src/remove_all.md --pipe > man/m_trie_remove_all.3

man/m_trie_trim.3: src/trim.md
	$(RONN) $(RFLAGS) src/trim.md --pipe > man/m_trie_trim.3

man/m_trie_hash.3: src/hash.md
	$(RONN) $(RFLAGS) src/hash.md --pipe > man/m_trie_hash.3

clean:
	rm -r ./man/*.3
