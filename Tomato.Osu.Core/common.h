//
// Osu Core
// ����ͷ�ļ�
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-03
//
#pragma once

#define DEFINE_NS_OSU_CORE namespace Tomato { namespace Osu {namespace Core {
#define END_NS_OSU_CORE }}}
#define NS_OSU_CORE Tomato::Osu::Core

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr)) throw Platform::Exception::CreateException(hr);
}

template<typename T>
inline Windows::Foundation::TimeSpan MSToTimeSpan(T ms)
{
	return Windows::Foundation::TimeSpan{ static_cast<long long>(ms * 10000) };
}