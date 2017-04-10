RONN=ronn
RFLAGS=--roff --warnings --organization=lovasko --manual=m_trie

.PHONY: clean all

all:                   \
	man/m_trie_init.3m   \
	man/m_trie_free.3m   \
	man/m_trie_insert.3m \
	man/m_trie_search.3m \
	man/m_trie_remove.3m \
	man/m_trie_trim.3m   \
	man/m_trie_hash.3m

man/m_trie_init.3m: src/init.md
	$(RONN) $(RFLAGS) <src/init.md >man/m_trie_init.3m

man/m_trie_free.3m: src/free.md
	$(RONN) $(RFLAGS) <src/free.md >man/m_trie_free.3m

man/m_trie_insert.3m: src/insert.md
	$(RONN) $(RFLAGS) <src/insert.md >man/m_trie_insert.3m

man/m_trie_search.3m: src/search.md
	$(RONN) $(RFLAGS) <src/search.md >man/m_trie_search.3m

man/m_trie_remove.3m: src/remove.md
	$(RONN) $(RFLAGS) <src/remove.md >man/m_trie_remove.3m

man/m_trie_trim.3m: src/trim.md
	$(RONN) $(RFLAGS) <src/trim.md >man/m_trie_trim.3m

man/m_trie_hash.3m: src/hash.md
	$(RONN) $(RFLAGS) <src/hash.md >man/m_trie_hash.3m

clean:
	rm -r ./man/*.3m
