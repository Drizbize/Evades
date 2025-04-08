#include "game.h"

int main()
{
    Game evades(1600, 900);

    Frame a(*evades.window.get());
    a.thickness = 10;
    //a.outlineColor = sf::Color(10, 27, 0);
    a.position = Udim2::fromScale(0.75, 0.25);
    a.anchorPoint = { 0.5, 0.5 };
    a.transparency = 0.9;

    Frame& child = a.addChild<Frame>(Udim2::fromScale(0.5, 0.5));
    child.thickness = 2;
    child.frameColor = sf::Color(100, 255, 0);
    //child.position = Udim2::fromScale(0.5, 0.5);
    //child.anchorPoint = { 0.5, 0.5 };
    child.outlineColor = sf::Color(255, 0, 0);
    child.transparency = 0.95;

    Frame& child2 = child.addChild<Frame>(Udim2::fromScale(0.5, 0.5));
    child2.position = Udim2::fromScale(0.5, 0.5);
    child2.anchorPoint = { 0.5, 0.5 };
    child2.frameColor = sf::Color(0, 255, 0);
    child2.outlineColor = sf::Color(0, 0, 255);

    //child2.anchorPoint += sf::Vector2f(0.5, 0.5);

    sf::Image Arena;
    sf::Image Wall3;

    Arena.loadFromFile("resources/area.png");
    Wall3.loadFromFile("resources/Wall3.png");

    sf::Texture texture;
    texture.resize({48, 48});
    

    sf::Sprite sp(texture);
    sp.setTexture(texture);

    int imPos = 0;

    TweenService tween(4, true, std::bind(&Igui::update, &a));
    tween.addTween(a.position.get(), Udim2::fromScale(0.25f, 0.75f), tweenStyle::Cube);
    tween.addTween(child.position.get(), Udim2::fromScale(1.f, 1.f), tweenStyle::Linear);
    tween.addTween(child.anchorPoint.get(), sf::Vector2f(1.f, 1.f), tweenStyle::Linear);
    tween.addTween(imPos, 500, tweenStyle::Linear);

    while (evades.window->isOpen())
    {
        while (const std::optional event = evades.window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                evades.window->close();
        }

        evades.logic();

        tween.start();
        tween.play(evades.dt);

        evades.window->clear(sf::Color(199, 226, 237));

        a.render();

        texture.update(Arena);
        sp.setPosition(sf::Vector2f(50, 50));
        evades.window->draw(sp);

        texture.update(Wall3);
        sp.setPosition(sf::Vector2f(imPos, imPos));
        evades.window->draw(sp);

        evades.window->display();
        //evades.render();

        evades.update_dt();
    }

    return 0;
}