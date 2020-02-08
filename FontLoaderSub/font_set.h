#pragma once

#include <stdint.h>
#include "util.h"

typedef struct _FS_Set FS_Set;

typedef struct {
  uint32_t num_file;
  uint32_t num_face;
} FS_Stat;

// feel free to change its order (except for the last one)
typedef enum {
  FS_FmtNone,  // least preferred
  FS_FmtOTF,
  FS_FmtTTF,
  FS_FmtTTC,  // most preferred
  FS_FmtMax   // number of formats
} FS_Format;

typedef struct {
  const wchar_t *tag;
  const wchar_t *face;
  const wchar_t *ver;
  FS_Format format;
} FS_Index;

typedef struct {
  // private:
  FS_Set *set;
  uint32_t query_id;
  uint32_t index_id;
  // public:
  FS_Index info;
} FS_Iter;

int fs_create(allocator_t *alloc, FS_Set **out);

int fs_free(FS_Set *s);

int fs_stat(FS_Set *s, FS_Stat *stat);

int fs_add_font(FS_Set *s, const wchar_t *tag, void *buf, size_t size);

int fs_build_index(FS_Set *s);

int fs_iter_new(FS_Set *s, const wchar_t *face, FS_Iter *it);

int fs_iter_next(FS_Iter *it);

int fs_cache_load(const wchar_t *path, allocator_t *alloc, FS_Set **out);

int fs_cache_dump(FS_Set *s, const wchar_t *path);

int fs_blacklist_clear(FS_Set *s);

int fs_blacklist_add(FS_Set *s, const wchar_t *path, size_t cch);

int fs_blacklist_match(FS_Set *S, const wchar_t *path);
