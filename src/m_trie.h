#ifndef M_TRIE_H
#define M_TRIE_H

#include <stdlib.h>
#include <stdint.h>
#include <m_list.h>

#define M_TRIE_OK                  0
#define M_TRIE_E_NULL              1
#define M_TRIE_E_NOT_FOUND         2
#define M_TRIE_E_KEY_INVALID       3
#define M_TRIE_E_EXISTS            4
#define M_TRIE_E_COPY_INVALID      5
#define M_TRIE_E_OVERWRITE_INVALID 6
#define M_TRIE_E_PREFIX            7
#define M_TRIE_E_INVALID_CODE      8
#define M_TRIE_E_NOT_STORED        9
#define M_TRIE_E_MAX               9

#define M_TRIE_OVERWRITE_ALLOW   0
#define M_TRIE_OVERWRITE_PREVENT 1

#define M_TRIE_COPY_DEEP    0
#define M_TRIE_COPY_SHALLOW 1

#define M_TRIE_REMOVE_NO_CLEANUP 1
#define M_TRIE_REMOVE_PREFIX     2

#define M_TRIE_AUX_STORE_NONE   0
#define M_TRIE_AUX_STORE_KEYS   1
#define M_TRIE_AUX_STORE_VALUES 2

/* 
 * HACK
 * root in the m_trie structure is a pointer to a struct __m_node, disguised as
 * void* in order not to pollute the namespace of the user of the library.
 */
struct m_trie {
	void* root;
	struct m_list keys;
	struct m_list values;
	int16_t (*hash)(char);
	uint8_t children_count;
	uint8_t aux_store;
	char padding[6];
};

int m_trie_init(struct m_trie* trie, int16_t (*hash)(char), uint8_t aux_store);
int m_trie_set(struct m_trie* trie, char* key, uint32_t key_length, uint8_t copy, uint8_t overwrite, void* data, size_t data_size);
int m_trie_get(struct m_trie* trie, char* key, uint32_t key_length, void** out_data);
int m_trie_keys(struct m_trie* trie, struct m_list** out_keys);
int m_trie_values(struct m_trie* trie, struct m_list** out_values);
int m_trie_memory_usage(struct m_trie* trie, uint64_t* out_usage);
int m_trie_children_stats(struct m_trie* trie, uint64_t** out_stats);
int m_trie_remove(struct m_trie* trie, char* key, uint32_t key_length, int mode);
int m_trie_error_string(int code, char** out_error_string);
int16_t m_trie_generic_byte_hash(char key);

#endif

