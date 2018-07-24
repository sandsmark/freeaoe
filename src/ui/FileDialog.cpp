#include "FileDialog.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "fonts/Alegreya-Bold.latin.h"

FileDialog::FileDialog()
{
}

bool FileDialog::setup(int width, int height)
{
    m_renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "freeaoe");
    m_renderWindow->setSize(sf::Vector2u(width, height));
    m_renderWindow->setFramerateLimit(60);
    m_renderWindow->setView(sf::View(sf::FloatRect(0, 0, width, height)));

    m_font = std::make_unique<sf::Font>();
    m_font->loadFromMemory(resource_Alegreya_Bold_latin_data, resource_Alegreya_Bold_latin_size);

    const Size buttonSize(200, 50);

    m_okButton = std::make_unique<Button>("OK", *m_font, ScreenRect(ScreenPos(200, 700), buttonSize));

    m_cancelButton = std::make_unique<Button>("Cancel", *m_font, ScreenRect(ScreenPos(624, 700), buttonSize));
    m_cancelButton->enabled = true;

    {
        m_description = std::make_unique<sf::Text>("Please select the directory containing your Age of Empires 2 installation.", *m_font);
        m_description->setCharacterSize(24);
        const int descWidth = m_description->getLocalBounds().width;
        m_description->setPosition(width/2 - descWidth/2, 10);
        m_description->setFillColor(sf::Color::White);
    }

    m_fileList = std::make_unique<ListView>(*m_font, ScreenRect(ScreenPos(width/2 - width*3/8, 50), Size(width*3/4, 550)));
    m_fileList->setCurrentPath("/tmp/");

    return true;
}

std::string FileDialog::getPath()
{
    std::string ret;

    while (m_renderWindow->isOpen()) {
        m_renderWindow->clear(sf::Color::Black);

        // Process events
        sf::Event event;
        if (!m_renderWindow->waitEvent(event)) {
            WARN << "failed to get event";
            break;
        }

        if (event.type == sf::Event::Closed) {
            m_renderWindow->close();
            continue;
        }

        if (m_cancelButton->checkClick(event)) {
            m_renderWindow->close();
        }

        if (m_okButton->checkClick(event)) {
            m_renderWindow->close();
            ret = "foo";
        }

        m_fileList->handleEvent(event);

        m_cancelButton->render(m_renderWindow.get());
        m_okButton->render(m_renderWindow.get());
        m_fileList->render(m_renderWindow.get());
        m_renderWindow->draw(*m_description);
        m_renderWindow->display();
    }

    return ret;
}

Button::Button(const std::string &text, const sf::Font &font, const ScreenRect rect) :
    m_rect(rect)
{
    m_text = std::make_unique<sf::Text>(text, font);
    m_text->setCharacterSize(24);
    const int textWidth = m_text->getLocalBounds().width;
    const int textHeight = m_text->getLocalBounds().height;
    m_text->setPosition(m_rect.x + (m_rect.width/2 - textWidth/2), m_rect.y + (m_rect.height/2 - textHeight));

    m_background = std::make_unique<sf::RectangleShape>();

    m_background->setOutlineThickness(2);
    m_background->setPosition(m_rect.topLeft());
    m_background->setSize(m_rect.size());
}

bool Button::checkClick(const sf::Event &event)
{
    if (!enabled) {
        m_pressed = false;
        return false;
    }

    if (event.type == sf::Event::MouseMoved) {
        ScreenPos mousePos(event.mouseMove.x, event.mouseMove.y);

        if (!m_rect.contains(mousePos)) {
            m_pressed = false;
        }

        return false;
    }

    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased) {
        return false;
    }

    ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);

    if (!m_rect.contains(mousePos)) {
        m_pressed = false;

        return false;
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        m_pressed = true;
        return false;
    }

    if (m_pressed) {
        return true;
    } else {
        return false;
    }
}

void Button::render(sf::RenderWindow *window)
{
    if (!enabled) {
        m_background->setOutlineColor(sf::Color(128, 128, 128));
        m_background->setFillColor(sf::Color(64, 64, 64));
        m_text->setFillColor(sf::Color(128, 128, 128));
    } else if (m_pressed) {
        m_background->setOutlineColor(sf::Color::Black);
        m_background->setFillColor(sf::Color::White);
        m_text->setFillColor(sf::Color::Black);
    } else {
        m_background->setOutlineColor(sf::Color::White);
        m_background->setFillColor(sf::Color::Black);
        m_text->setFillColor(sf::Color::White);
    }
    window->draw(*m_background);
    window->draw(*m_text);
}

ListView::ListView(const sf::Font &font, const ScreenRect rect) :
    m_rect(rect)
{
    m_itemHeight = rect.height / numVisible;

    for (int i=0; i<numVisible; i++) {
        std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>("-", font);
        text->setCharacterSize(18);
        text->setOutlineColor(sf::Color::Black);
        text->setOutlineThickness(2);
        const int textHeight = text->getLocalBounds().height;
        text->setPosition(rect.x + 10, rect.y + i * m_itemHeight + textHeight/3);

        m_texts.push_back(std::move(text));
    }

    m_background = std::make_unique<sf::RectangleShape>();

    m_background->setOutlineThickness(2);
    m_background->setPosition(m_rect.topLeft() - ScreenPos(2, 2));
    m_background->setSize(Size(m_rect.width + 4, m_rect.height + 4));
    m_background->setFillColor(sf::Color::Transparent);
    m_background->setOutlineColor(sf::Color::White);

    m_selectedOutline = std::make_unique<sf::RectangleShape>();
    m_selectedOutline->setOutlineThickness(1);
    m_selectedOutline->setPosition(m_rect.topLeft());
    m_selectedOutline->setSize(Size(m_rect.width - 20, m_itemHeight));
    m_selectedOutline->setFillColor(sf::Color::White);
    m_selectedOutline->setOutlineColor(sf::Color::Transparent);

    m_scrollBar = std::make_unique<sf::RectangleShape>();
    m_scrollBar->setOutlineThickness(2);
    m_scrollBar->setPosition(m_rect.topRight() + ScreenPos(-19, 5));
    m_scrollBar->setSize(Size(18, 10));
    m_scrollBar->setFillColor(sf::Color::White);
    m_scrollBar->setOutlineColor(sf::Color::Transparent);

    updateScrollbar();
}

void ListView::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved) {
        ScreenPos mousePos(event.mouseMove.x, event.mouseMove.y);

        if (!m_pressed) {
            return;
        }

        if (m_pressed && mousePos.x > m_rect.x + m_rect.width - 20) {
            moveScrollbar(mousePos.y);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        m_pressed = false;
        return;
    }

    if (event.type != sf::Event::MouseButtonPressed) {
        return;
    }

    ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
    if (!m_rect.contains(mousePos)) {
        return;
    }

    // scrollbar hit
    if (mousePos.x > m_rect.x + m_rect.width - 20) {
        moveScrollbar(mousePos.y);
        m_pressed = true;
        return;
    }

    int index = (event.mouseButton.y - m_rect.y) / m_itemHeight + m_offset;

    if (index >= m_list.size()) {
        return;
    }

    m_currentItem = index;
}

void ListView::render(sf::RenderWindow *window)
{
    window->draw(*m_background);

    if (m_currentItem - m_offset > 0 && m_currentItem - m_offset < numVisible) {
        m_selectedOutline->setPosition(ScreenPos(m_rect.x, m_rect.y + (m_currentItem - m_offset) * m_itemHeight));
        window->draw(*m_selectedOutline);
    }

    for (std::unique_ptr<sf::Text> &text : m_texts) {
        window->draw(*text);
    }

    window->draw(*m_scrollBar);
}

void ListView::setCurrentPath(const std::filesystem::path &path)
{
    if (path == m_currentPath) {
        return;
    }

    m_list.clear();
    for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(path)) {
        m_list.push_back(entry.path());
    }
    std::sort(m_list.begin(), m_list.end(), [](const std::filesystem::path &a, const std::filesystem::path &b){
        const bool aIsDir = std::filesystem::is_directory(a);
        const bool bIsDir = std::filesystem::is_directory(b);
        if (aIsDir != bIsDir) {
            return !aIsDir < !bIsDir;
        }
        return a.filename() < b.filename();
    });

    m_currentItem = 0;
    m_offset = 0;

    for (size_t i=0; i<m_texts.size(); i++) {
        if (i < m_list.size()) {
            std::string filename = m_list[i].filename().string();
            if (filename.size() > 40) {
                filename.resize(40);
                filename += "...";
            }
            if (std::filesystem::is_directory(m_list[i])) {
                m_texts[i]->setString("[" + filename + "]");
            } else{
                m_texts[i]->setString(filename);
            }
        } else {
            m_texts[i]->setString("");
        }
    }

    updateScrollbar();
}

void ListView::setOffset(int offset)
{
    if (offset < 0) {
        offset = 0;
    }

    if (offset > m_list.size() - numVisible) {
        offset = m_list.size() - numVisible;
    }

    if (offset == m_offset) {
        return;
    }

    m_offset = offset;

    for (size_t i=0; i<m_texts.size(); i++) {
        if (i+m_offset < m_list.size()) {
            std::string filename = m_list[i+m_offset].filename().string();
            if (filename.size() > 40) {
                filename.resize(40);
                filename += "...";
            }
            if (std::filesystem::is_directory(m_list[i+m_offset])) {
                m_texts[i]->setString("[" + filename + "]");
            } else{
                m_texts[i]->setString(filename);
            }
        } else {
            m_texts[i]->setString("");
        }
    }

    updateScrollbar();
}

std::string ListView::currentText() const
{
    int index = m_currentItem + m_offset;
    if (index < m_list.size()) {
        return m_list[index];
    }

    return "";

}

void ListView::updateScrollbar() const
{
    if (m_list.empty()) {
        m_scrollBar->setSize(Size(0, 0));
        return;
    }

    int scrollbarSize =  m_rect.height * (float(numVisible) / m_list.size());
    m_scrollBar->setSize(Size(18, std::max(scrollbarSize, 20)));

    int scrollbarPos = m_rect.height * float(m_offset) / m_list.size();
    m_scrollBar->setPosition(m_rect.topRight() + ScreenPos(-19, scrollbarPos));
}

void ListView::moveScrollbar(int mouseY)
{
    float ratio = (mouseY - m_scrollBar->getSize().y/2 - m_rect.y) / m_rect.height;
    setOffset(m_list.size() * ratio);
}
