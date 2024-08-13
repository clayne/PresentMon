#pragma once

namespace pmon::util
{
	const char* BuildIdShortHash() noexcept;
	const char* BuildIdLongHash() noexcept;
	const char* BuildIdTimestamp() noexcept;
	const char* BuildIdUid() noexcept;
	bool BuildIdDirtyFlag() noexcept;
}