#ifndef SHIFTY_TWEEN_H
#define SHIFTY_TWEEN_H

#include <cmath>

class Tween {
public:
    template<typename T>
    static T Lerp(T start, T end, T t) {
        return start + (end - start) * t;
    }

    template<typename T>
    static T easeInSine(T t) {
        return (T) 1 - std::cos(t * (T) M_PI / (T) 2);
    }

    template<typename T>
    static T easeOutSine(T t) {
        return std::sin(t * (T) M_PI / (T) 2);
    }

    template<typename T>
    static T easeInOutSine(T t) {
        return -(std::cos((T) (T) M_PI * t) - (T) 1) / (T) 2;
    }

    template<typename T>
    static T easeInQuad(T t) {
        return t * t;
    }

    template<typename T>
    static T easeOutQuad(T t) {
        return (T) 1 - ((T) 1 - t) * ((T) 1 - t);
    }

    template<typename T>
    static T easeInOutQuad(T t) {
        return t < (T) 0.5 ? (T) 2 * t * t : (T) 1 - std::pow(-(T) 2 * t + (T) 2, (T) 2) / (T) 2;
    }

    template<typename T>
    static T easeInCubic(T t) {
        return t * t * t;
    }

    template<typename T>
    static T easeOutCubic(T t) {
        return (T) 1 - std::pow((T) 1 - t, (T) 3);
    }

    template<typename T>
    static T easeInOutCubic(T t) {
        return t < (T) 0.5 ? (T) 4 * t * t * t : (T) 1 - std::pow(-(T) 2 * t + (T) 2, (T) 3) / (T) 2;
    }

    template<typename T>
    static T easeInQuart(T t) {
        return t * t * t * t;
    }

    template<typename T>
    static T easeOutQuart(T t) {
        return (T) 1 - std::pow((T) 1 - t, (T) 4);
    }

    template<typename T>
    static T easeInOutQuart(T t) {
        return t < (T) 0.5 ? 8 * t * t * t * t : (T) 1 - std::pow(-(T) 2 * t + (T) 2, (T) 4) / (T) 2;
    }

    template<typename T>
    static T easeInQuint(T t) {
        return t * t * t * t * t;
    }

    template<typename T>
    static T easeOutQuint(T t) {
        return (T) 1 - std::pow((T) 1 - t, 5);
    }

    template<typename T>
    static T easeInOutQuint(T t) {
        return t < (T) 0.5 ? 16 * t * t * t * t * t : (T) 1 - std::pow(-(T) 2 * t + (T) 2, 5) / (T) 2;
    }

    template<typename T>
    static T easeInExpo(T t) {
        return t == (T) 0 ? (T) 0 : std::pow((T) 2, (T) 10 * t - (T) 10);
    }

    template<typename T>
    static T easeOutExpo(T t) {
        return t == (T) 1 ? (T) 1 : (T) 1 - std::pow((T) 2, -(T) 10 * t);
    }

    template<typename T>
    static T easeInOutExpo(T t) {
        return t == (T) 0
                   ? (T) 0
                   : t == (T) 1
                         ? (T) 1
                         : t < (T) 0.5
                               ? std::pow((T) 2, (T) 20 * t - (T) 10) / (T) 2
                               : ((T) 2 - std::pow((T) 2, -(T) 20 * t + (T) 10)) / (T) 2;
    }

    template<typename T>
    static T easeInCirc(T t) {
        return (T) 1 - std::sqrt((T) 1 - t * t);
    }

    template<typename T>
    static T easeOutCirc(T t) {
        return std::sqrt((T) 1 - std::pow(t - (T) 1, (T) 2));
    }

    template<typename T>
    static T easeInOutCirc(T t) {
        return t < (T) 0.5
                   ? ((T) 1 - std::sqrt((T) 1 - t * t)) / (T) 2
                   : (std::sqrt((T) 1 - std::pow(-(T) 2 * t + (T) 2, (T) 2)) + (T) 1) / (T) 2;
    }

    template<typename T>
    static T easeInBack(T t) {
        const T c1 = (T) 1.70158f;
        const T c3 = c1 + (T) 1;

        return c3 * t * t * t - c1 * t * t;
    }

    template<typename T>
    static T easeOutBack(T t) {
        const T c1 = (T) 1.70158f;
        const T c3 = c1 + (T) 1;

        return (T) 1 + c3 * std::pow(t - (T) 1, (T) 3) + c1 * std::pow(t - (T) 1, (T) 2);
    }

    template<typename T>
    static T easeInOutBack(T t) {
        const T c1 = (T) 1.70158f;
        const T c2 = c1 * (T) 1.525f;

        return t < (T) 0.5
                   ? (std::pow((T) 2 * t, (T) 2) * ((c2 + (T) 1) * (T) 2 * t - c2)) / (T) 2
                   : (std::pow((T) 2 * t - (T) 2, (T) 2) * ((c2 + (T) 1) * (t * (T) 2 - (T) 2) + c2) + (T) 2) / (T) 2;
    }

    template<typename T>
    static T easeInElastic(T t) {
        const T c4 = ((T) 2 * (T) M_PI) / (T) 3;
        return t == (T) 0
                   ? (T) 0
                   : t == (T) 1
                         ? (T) 1
                         : -std::pow((T) 2, (T) 10 * t - (T) 10) *
                           std::sin((t * (T) 10 - (T) 10.75f) * c4);
    }

    template<typename T>
    static T easeOutElastic(T t) {
        const T c4 = ((T) 2 * (T) M_PI) / (T) 3;
        return t == (T) 0
                   ? (T) 0
                   : t == (T) 1
                         ? (T) 1
                         : std::pow((T) 2, -(T) 10 * t) * std::sin((t * (T) 10 - 0.75f) * c4) + (T) 1;
    }

    template<typename T>
    static T easeInOutElastic(T t) {
        const T c4 = ((T) 2 * (T) M_PI) / (T) 3;
        return t == (T) 0
                   ? (T) 0
                   : t == (T) 1
                         ? (T) 1
                         : t < (T) 0.5
                               ? -(std::pow((T) 2, (T) 20 * t - (T) 10) * std::sin(((T) 20 * t - 11.125f) * c4)) / (T) 2
                               : (std::pow((T) 2, -(T) 20 * t + (T) 10) * std::sin(((T) 20 * t - 11.125f) * c4)) / (T) 2
                                 + (T) 1;
    }
};

#endif //SHIFTY_TWEEN_H
