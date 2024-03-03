#pragma once

#include "config.g.h"

namespace winrt::SentimentAnalysis::implementation
{
    struct config : configT<config>
    {
        config() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::SentimentAnalysis::factory_implementation
{
    struct config : configT<config, implementation::config>
    {
    };
}
