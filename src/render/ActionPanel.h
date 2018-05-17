#ifndef ACTIONPANEL_H
#define ACTIONPANEL_H

#include <mechanics/IState.h>

#include <memory>

class SfmlRenderTarget;
class EntityManager;

class ActionPanel : public IState
{
public:
    ActionPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget);
    ActionPanel() = delete;

    bool init() override;
    void handleEvent(sf::Event event) override;
    bool update(Time time) override;
    void draw() override;

    void setEntityManager(const std::shared_ptr<EntityManager> &entityManager);

    ScreenRect rect() const;

    void releaseButtons();

private:
    std::shared_ptr<SfmlRenderTarget> m_renderTarget;
    std::shared_ptr<EntityManager> m_entityManager;
    ScreenRect m_rect;

};

#endif // ACTIONPANEL_H
