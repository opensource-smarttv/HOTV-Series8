// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WTF_AtomicStringTable_h
#define WTF_AtomicStringTable_h

#include "wtf/Allocator.h"
#include "wtf/HashSet.h"
#include "wtf/WTFExport.h"
#include "wtf/WTFThreadData.h"
#include "wtf/text/StringHash.h"
#include "wtf/text/StringImpl.h"

namespace WTF {

// The underlying storage that keeps the map of unique AtomicStrings. This is
// not thread safe and each WTFThreadData has one.
class WTF_EXPORT AtomicStringTable final {
    USING_FAST_MALLOC(AtomicStringTable);
    WTF_MAKE_NONCOPYABLE(AtomicStringTable);
public:
    AtomicStringTable();
    ~AtomicStringTable();

    // Gets the shared table for the current thread.
    static AtomicStringTable& instance()
    {
        return wtfThreadData().getAtomicStringTable();
    }

    // Used by system initialization to preallocate enough storage for all of
    // the static strings.
    void reserveCapacity(unsigned);

    // Adding a StringImpl.
    StringImpl* add(StringImpl*);
    PassRefPtr<StringImpl> add(StringImpl*, unsigned offset, unsigned length);

    // Adding an LChar.
    PassRefPtr<StringImpl> add(const LChar*, unsigned length);

    // Adding a UChar.
    PassRefPtr<StringImpl> add(const UChar*, unsigned length);
    PassRefPtr<StringImpl> add(const UChar*, unsigned length, unsigned existingHash);
    PassRefPtr<StringImpl> add(const UChar*);

    // Adding UTF8.
    // Returns null if the characters contain invalid utf8 sequences.
    // Pass null for the charactersEnd to automatically detect the length.
    PassRefPtr<StringImpl> addUTF8(const char* charactersStart, const char* charactersEnd);

    // This is for ~StringImpl to unregister a string before destruction since
    // the table is holding weak pointers. It should not be used directly.
    void remove(StringImpl*);

private:
    template<typename T, typename HashTranslator>
    inline PassRefPtr<StringImpl> addToStringTable(const T& value);

    template<typename CharacterType>
    inline HashSet<StringImpl*>::iterator find(const StringImpl*);

    HashSet<StringImpl*> m_table;
};

} // namespace WTF

using WTF::AtomicStringTable;

#endif
