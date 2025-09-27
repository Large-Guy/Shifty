![SHIFTY](res/img/logo.svg)

*The ultimate, minimalist browsing experience.*

## About

Shifty works through a **single shortcut**,
> **double-shift** → opens the **command palette**

From the palette you can run any command you'd expect in a
modern browser (and more!) in just a few keystrokes.

Shifty has **zero native ui** besides a lightweight command palette,
to keep your experience as distraction free as possible.

---

## Why use Shifty?

### DON'T!

---
> ⚠️ **Warning: Very Early Alpha**
> This is a very early version of shifty, in fact it's unusable. Plans are to
> eventually use Ladybird's Web Engine, allowing
> for greater optimization and control.
---

### Why use it in the Future?

- **More keyboard usage** → More productivity! ✨
- **Extremely Minimal UI** → No time getting distracted or searching for themes!
- **Doesn't feel like a web browser** → No UI makes websites feel like native applications!

## Goals

- **NO MOUSE** → No mouse should be required to explore the web

## Contributor Info

If you do want to help with development, there are a few odd decisions I made about this project's architecture, but I
think they are beneficial and keep the project a lot cleaner.

### 1. ECS

This software is structured using an ECS. Which is more common in video games, but I think it can help
with software architecture as well.

### 2. Event Buses

All application operations happen through events. This is most visible
in [TextEditSystems.h](src/Systems/TextEditSystems.h). Each ECS System only handles ONE event.
This keeps things simple and modular.