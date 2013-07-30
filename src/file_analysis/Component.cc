// See the file "COPYING" in the main distribution directory for copyright.

#include "Component.h"
#include "Manager.h"

#include "../Desc.h"
#include "../util.h"

using namespace file_analysis;

file_analysis::Tag::type_t Component::type_counter = 0;

Component::Component(const char* arg_name, factory_callback arg_factory,
                     file_analysis::Tag::subtype_t arg_subtype)
	: plugin::Component(plugin::component::FILE_ANALYZER)
	{
	name = copy_string(arg_name);
	canon_name = canonify_name(arg_name);
	factory = arg_factory;

	tag = file_analysis::Tag(++type_counter, arg_subtype);
	}

Component::Component(const Component& other)
	: plugin::Component(Type())
	{
	name = copy_string(other.name);
	canon_name = copy_string(other.canon_name);
	factory = other.factory;
	tag = other.tag;
	}

Component::~Component()
	{
	delete [] name;
	delete [] canon_name;
	}

file_analysis::Tag Component::Tag() const
	{
	return tag;
	}

void Component::Describe(ODesc* d) const
	{
	plugin::Component::Describe(d);
	d->Add(name);
	d->Add(" (");

	if ( factory )
		{
		d->Add("ANALYZER_");
		d->Add(canon_name);
		}

	d->Add(")");
	}

Component& Component::operator=(const Component& other)
	{
	if ( &other != this )
		{
		name = copy_string(other.name);
		factory = other.factory;
		tag = other.tag;
		}

	return *this;
	}
