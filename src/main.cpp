// // Copyright 2020 Arthur Sonzogni. All rights reserved.
// // Use of this source code is governed by the MIT license that can be found in
// // the LICENSE file.
// #include <memory>  // for allocator, __shared_ptr_access, shared_ptr
// #include <string>  // for string
 
// #include "ftxui/component/captured_mouse.hpp"  // for ftxui
// #include "ftxui/component/component.hpp"  // for Input, Renderer, ResizableSplitLeft
// #include "ftxui/component/component_base.hpp"  // for ComponentBase, Component
// #include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
// #include "ftxui/dom/elements.hpp"  // for operator|, separator, text, Element, flex, vbox, border
 
// int main() {
//   using namespace ftxui;
 
//   std::string content_1;
//   std::string content_2;
//   auto textarea_1 = Input(&content_1);
//   auto textarea_2 = Input(&content_2);
//   int size = 50;
//   auto layout = ResizableSplitLeft(textarea_1, textarea_2, &size);
 
//   auto component = Renderer(layout, [&] {
//     return vbox({
//                text("Input:"),
//                separator(),
//                layout->Render() | flex,
//            }) |
//            border;
//   });
 
//   auto screen = ScreenInteractive::Fullscreen();
//   screen.Loop(component);
// }

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/util/ref.hpp>
#include <iostream>
#include <string>

int main(void) {
    using namespace ftxui;

    std::string message;

    InputOption style_1 = InputOption::Default();
    style_1.transform = [](InputState state) {
        state.element |= bgcolor(Color::Black);
        state.element |= color(Color::Cyan3);
        return state.element;  
    };
    Component component_message_input = Input(&message, "Hello", style_1);

    auto component = Container::Horizontal({
            component_message_input
        });

    auto renderer_left = Renderer(component_message_input, [&] {
        return vbox({
                text("You: ") | bold | color(Color::Cyan3),
                component_message_input->Render()
            });
    });

    auto renderer_right = Renderer([&] {
        return vbox({
                paragraph("You from over there: " + message) | bold | color(Color::MediumTurquoise)
            });
    });

    int size_renderer_left = 50;
    auto renderer = ResizableSplitLeft(renderer_left, renderer_right, &size_renderer_left);

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);
 
    return EXIT_SUCCESS;
}
