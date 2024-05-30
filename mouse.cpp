#include <functional>
#include <vector>
class EventDispatcher {
public:
    using MouseCallback = std::function<void(const sf::Event::MouseButtonEvent&)>;

    void addMousePressCallback(MouseCallback callback) {
        mousePressCallbacks.push_back(callback);
    }

    void addMouseReleaseCallback(MouseCallback callback) {
        mouseReleaseCallbacks.push_back(callback);
    }

    void dispatch(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (const auto& callback : mousePressCallbacks) {
                callback(event.mouseButton);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            for (const auto& callback : mouseReleaseCallbacks) {
                callback(event.mouseButton);
            }
        }
    }

private:
    std::vector<MouseCallback> mousePressCallbacks;
    std::vector<MouseCallback> mouseReleaseCallbacks;
};