/*
 * Copyright (c) 2020, Matthew Olsson <mattco@serenityos.org>
 * Copyright (c) 2022-2023, Linus Groh <linusg@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>
#include <LibGC/CellAllocator.h>
#include <LibJS/Export.h>
#include <LibJS/Heap/Cell.h>

namespace JS {

class JS_API Symbol final : public Cell {
    GC_CELL(Symbol, Cell);
    GC_DECLARE_ALLOCATOR(Symbol);

public:
    [[nodiscard]] static GC::Ref<Symbol> create(VM&, Optional<String> description, bool is_global);

    virtual ~Symbol() = default;

    Optional<String> const& description() const { return m_description; }
    bool is_global() const { return m_is_global; }

    ErrorOr<String> descriptive_string() const;
    Optional<String> key() const;

private:
    Symbol(Optional<String>, bool);

    Optional<String> m_description;
    bool m_is_global;
};

}
