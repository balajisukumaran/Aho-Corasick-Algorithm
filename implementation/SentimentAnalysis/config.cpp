#include "pch.h"
#include "config.h"
#if __has_include("config.g.cpp")
#include "config.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SentimentAnalysis::implementation
{
    int32_t config::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void config::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void config::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
