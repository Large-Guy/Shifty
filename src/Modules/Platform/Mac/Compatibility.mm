#include "Compatibility.hpp"

#include "SDL3/SDL.h"
#include "SDL3/SDL_video.h"
#include <stdexcept>
#import <Cocoa/Cocoa.h>

void* injectMacVibrancy(SDL_Window *window) {
    SDL_PropertiesID properties = SDL_GetWindowProperties(window);
    auto *win = (__bridge NSWindow *) SDL_GetPointerProperty(properties, "SDL.window.cocoa.window", nullptr);

    if (!win)
        throw std::runtime_error("Cocoa window was not valid!");

    win.opaque = NO;
    win.backgroundColor = [NSColor clearColor];

    NSVisualEffectView *blurView = [[NSVisualEffectView alloc] initWithFrame:win.contentView.bounds];
    blurView.material = NSVisualEffectMaterialUnderWindowBackground;
    blurView.blendingMode = NSVisualEffectBlendingModeWithinWindow;
    blurView.state = NSVisualEffectStateActive;
    blurView.translatesAutoresizingMaskIntoConstraints = NO; 

    [win.contentView addSubview:blurView positioned:NSWindowBelow relativeTo:nil];

    [NSLayoutConstraint activateConstraints:@[
            [blurView.leadingAnchor constraintEqualToAnchor:win.contentView.leadingAnchor],
            [blurView.trailingAnchor constraintEqualToAnchor:win.contentView.trailingAnchor],
            [blurView.topAnchor constraintEqualToAnchor:win.contentView.topAnchor],
            [blurView.bottomAnchor constraintEqualToAnchor:win.contentView.bottomAnchor]
    ]];
    
    return (void *) blurView;
}
