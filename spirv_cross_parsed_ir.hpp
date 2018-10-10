/*
 * Copyright 2018 Arm Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SPIRV_CROSS_PARSED_IR_HPP
#define SPIRV_CROSS_PARSED_IR_HPP

#include "spirv_common.hpp"
#include <stdint.h>
#include <unordered_map>
#include <vector>

namespace spirv_cross
{
class ParsedIR
{
public:
	void set_id_bounds(uint32_t bounds);

	std::vector<uint32_t> spirv;
	std::vector<Variant> ids;
	std::vector<Meta> meta;
	std::vector<spv::Capability> declared_capabilities;
	std::vector<std::string> declared_extensions;
	std::vector<uint32_t> global_variables;
	std::vector<uint32_t> aliased_variables;

	std::unordered_set<uint32_t> loop_blocks;
	std::unordered_set<uint32_t> continue_blocks;
	std::unordered_set<uint32_t> loop_merge_targets;
	std::unordered_set<uint32_t> selection_merge_targets;
	std::unordered_set<uint32_t> multiselect_merge_targets;
	std::unordered_map<uint32_t, uint32_t> continue_block_to_loop_header;

	// Normally, we'd stick SPIREntryPoint in ids array, but it conflicts with SPIRFunction.
	// Entry points can therefore be seen as some sort of meta structure.
	std::unordered_map<uint32_t, SPIREntryPoint> entry_points;
	uint32_t default_entry_point = 0;

	struct Source
	{
		uint32_t version = 0;
		bool es = false;
		bool known = false;
		bool hlsl = false;

		Source() = default;
	};

	Source source;

	void set_name(uint32_t id, const std::string &name);
	void set_member_name(uint32_t id, uint32_t index, const std::string &name);

	void set_decoration(uint32_t id, spv::Decoration decoration, uint32_t argument = 0);
	void set_decoration_string(uint32_t id, spv::Decoration decoration, const std::string &argument);
	bool has_decoration(uint32_t id, spv::Decoration decoration) const;
	void set_member_decoration(uint32_t id, uint32_t index, spv::Decoration decoration, uint32_t argument = 0);
	void set_member_decoration_string(uint32_t id, uint32_t index, spv::Decoration decoration,
	                                  const std::string &argument);
	const Bitset &get_member_decoration_bitset(uint32_t id, uint32_t index) const;
	const Bitset &get_decoration_bitset(uint32_t id) const;
	const std::string &get_name(uint32_t id) const;

	void mark_used_as_array_length(uint32_t id);
	uint32_t increase_bound_by(uint32_t count);
	Bitset get_buffer_block_flags(const SPIRVariable &var) const;

private:
	template <typename T>
	T &get(uint32_t id)
	{
		return variant_get<T>(ids[id]);
	}

	template <typename T>
	const T &get(uint32_t id) const
	{
		return variant_get<T>(ids[id]);
	}
};
} // namespace spirv_cross

#endif