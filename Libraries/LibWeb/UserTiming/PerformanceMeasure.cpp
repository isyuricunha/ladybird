/*
 * Copyright (c) 2023, Luke Wilde <lukew@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Bindings/PerformanceMeasurePrototype.h>
#include <LibWeb/HTML/StructuredSerialize.h>
#include <LibWeb/HTML/Window.h>
#include <LibWeb/HighResolutionTime/TimeOrigin.h>
#include <LibWeb/NavigationTiming/EntryNames.h>
#include <LibWeb/PerformanceTimeline/EntryTypes.h>
#include <LibWeb/UserTiming/PerformanceMeasure.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::UserTiming {

GC_DEFINE_ALLOCATOR(PerformanceMeasure);

PerformanceMeasure::PerformanceMeasure(JS::Realm& realm, String const& name, HighResolutionTime::DOMHighResTimeStamp start_time, HighResolutionTime::DOMHighResTimeStamp duration, JS::Value detail)
    : PerformanceTimeline::PerformanceEntry(realm, name, start_time, duration)
    , m_detail(detail)
{
}

PerformanceMeasure::~PerformanceMeasure() = default;

GC::Ref<PerformanceMeasure> PerformanceMeasure::create(JS::Realm& realm, String const& measure_name, HighResolutionTime::DOMHighResTimeStamp start_time, HighResolutionTime::DOMHighResTimeStamp duration, JS::Value detail)
{
    return realm.create<PerformanceMeasure>(realm, measure_name, start_time, duration, detail);
}

FlyString const& PerformanceMeasure::entry_type() const
{
    return PerformanceTimeline::EntryTypes::measure;
}

void PerformanceMeasure::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(PerformanceMeasure);
    Base::initialize(realm);
}

void PerformanceMeasure::visit_edges(JS::Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_detail);
}

}
