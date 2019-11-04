#include "FileDialog.h"

#include "core/Logger.h"
#include "core/Utility.h"
#include "global/Config.h"
#include "render/SfmlRenderTarget.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <stddef.h>
#include <algorithm>
#include <system_error>
#include <utility>

FileDialog::FileDialog()
{
}

bool FileDialog::setup(int width, int height)
{
    m_renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "freeaoe");
    m_renderWindow->setSize(sf::Vector2u(width, height));
    m_renderWindow->setView(sf::View(sf::FloatRect(0, 0, width, height)));
    m_renderTarget = std::make_shared<SfmlRenderTarget>(*m_renderWindow);



    {
        m_description = std::make_unique<sf::Text>("Please select the directory containing your Age of Empires 2 installation.", SfmlRenderTarget::defaultFont());
        m_description->setCharacterSize(20);
        const int descWidth = m_description->getLocalBounds().width;
        m_description->setPosition(width/2 - descWidth/2, 2);
        m_description->setFillColor(sf::Color::White);
    }

    const Size buttonSize(250, 50);

    m_fileList = std::make_unique<ListView>(SfmlRenderTarget::defaultFont(), ScreenRect(ScreenPos(width/2 - width*3/8, 55), Size(width*3/4, 550)));
    m_fileList->setCurrentPath(std::filesystem::current_path().string());

    m_okButton = std::make_unique<Button>("OK", ScreenRect(ScreenPos(m_fileList->rect().x, 700), buttonSize), m_renderTarget);

    m_cancelButton = std::make_unique<Button>("Cancel", ScreenRect(ScreenPos(m_fileList->rect().right() - buttonSize.width, 700), buttonSize), m_renderTarget);
    m_cancelButton->enabled = true;

    m_openDownloadUrlButton = std::make_unique<Button>("Download trial version", ScreenRect(ScreenPos(m_fileList->rect().center().x - buttonSize.width/2, 700), buttonSize), m_renderTarget);
    m_openDownloadUrlButton->enabled = true;

#if defined(__linux__)
    m_winePath = Config::winePath();
    if (!m_winePath.empty()) {
        if (std::filesystem::exists(m_winePath + "/drive_c")) {
            m_winePath += "/drive_c";
        }
        m_goToWineButton = std::make_unique<Button>("Go to Wine folder", ScreenRect(ScreenPos(m_fileList->rect().x, m_fileList->rect().bottom() + 10), buttonSize), m_renderTarget);
        m_goToWineButton->enabled = true;
    }
#endif

    return true;
}

std::string FileDialog::getPath()
{
    std::string ret;

    while (m_renderWindow->isOpen()) {
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

        if (m_openDownloadUrlButton->checkClick(event)) {
            util::openUrl("https://archive.org/details/AgeOfEmpiresIiTheConquerorsDemo", nullptr);
            continue;
        }

        if (m_cancelButton->checkClick(event)) {
            m_renderWindow->close();
        }

        if (m_okButton->checkClick(event)) {
            m_renderWindow->close();
            ret = m_fileList->currentText();
        }

#if defined(__linux__)
        if (m_goToWineButton) {
            if (m_goToWineButton->checkClick(event)) {
                m_fileList->setCurrentPath(std::filesystem::path(m_winePath));
            }
        }
#endif

        m_fileList->handleEvent(event);
        m_okButton->enabled = m_fileList->hasDataFolder;

        m_renderWindow->clear(sf::Color(32, 32, 32));
        m_openDownloadUrlButton->render(m_renderTarget);
        m_cancelButton->render(m_renderTarget);
        m_okButton->render(m_renderTarget);
        m_fileList->render(m_renderWindow.get());
        m_renderWindow->draw(*m_description);
        if (m_errorText) {
            m_renderWindow->draw(*m_errorText);
        }

#if defined(__linux__)
        if (m_goToWineButton) {
            m_goToWineButton->render(m_renderTarget);
        }
#endif
        m_renderWindow->display();
    }

    return ret;
}

void FileDialog::setErrorString(const std::string &error) noexcept
{
    m_errorText = std::make_unique<sf::Text>("Failed to load game data: " + error, SfmlRenderTarget::defaultFont());
    m_errorText->setCharacterSize(17);
    const int textWidth = m_errorText->getLocalBounds().width;
    m_errorText->setPosition(m_renderWindow->getSize().x/2 - textWidth/2, 25);
    m_errorText->setFillColor(sf::Color(255, 128, 128));
}

Button::Button(const std::string &text, const ScreenRect &rect, const IRenderTargetPtr &renderTarget) :
    m_rect(rect)
{
    m_text = renderTarget->createText();
    m_text->string = text;
    m_text->pointSize = 24;
    const int textWidth = m_text->size().width;
    const int textHeight = m_text->size().height;
    m_text->position.x = m_rect.x + (m_rect.width/2 - textWidth/2);
    m_text->position.y = m_rect.y + (m_rect.height/2 - textHeight);

    m_background.borderSize = 2;
    m_background.rect = m_rect;
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

    return m_pressed;
}

void Button::render(IRenderTargetPtr window)
{
    if (!enabled) {
        m_background.borderColor = Drawable::Color(128, 128, 128);
        m_background.fillColor = Drawable::Color(64, 64, 64);
        m_background.filled = true;
        m_text->color = Drawable::Color(128, 128, 128);
    } else if (m_pressed) {
        m_background.borderColor = Drawable::Black;
        m_background.fillColor = Drawable::White;
        m_background.filled = true;
        m_text->color = Drawable::Black;
    } else {
        m_background.borderColor = Drawable::White;
        m_background.fillColor = Drawable::Black;
        m_background.filled = true;
        m_text->color = Drawable::White;
    }
    window->draw(m_background);
    window->draw(m_text);
}

ListView::ListView(const sf::Font &font, const ScreenRect rect) :
    m_rect(rect)
{
    m_itemHeight = rect.height / numVisible;

    for (int i=0; i<numVisible; i++) {
        std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>("-", font);
        text->setCharacterSize(18);
        text->setOutlineColor(sf::Color::Black);
        text->setOutlineThickness(1);
        const int textHeight = text->getLocalBounds().height;
        text->setPosition(rect.x + 10, rect.y + i * m_itemHeight + textHeight/3);
        text->setOutlineColor(sf::Color::Transparent);

        m_texts.push_back(std::move(text));
    }

    m_background = std::make_unique<sf::RectangleShape>();

    m_background->setOutlineThickness(2);
    m_background->setPosition(m_rect.topLeft());// - ScreenPos(2, 2));
    m_background->setSize(Size(m_rect.width/* + 4*/, m_rect.height/* + 4*/));
    m_background->setFillColor(sf::Color::Black);
    m_background->setOutlineColor(sf::Color::White);

    m_selectedOutline = std::make_unique<sf::RectangleShape>();
    m_selectedOutline->setOutlineThickness(1);
    m_selectedOutline->setPosition(m_rect.topLeft());
    m_selectedOutline->setFillColor(sf::Color::White);
    m_selectedOutline->setOutlineColor(sf::Color::Transparent);

    m_scrollBar = std::make_unique<sf::RectangleShape>();
    m_scrollBar->setOutlineThickness(2);
    m_scrollBar->setPosition(m_rect.topRight() + ScreenPos(-20, 5));
    m_scrollBar->setSize(Size(0, 10));
    m_scrollBar->setFillColor(sf::Color(0, 0, 0, 128));
    m_scrollBar->setOutlineColor(sf::Color::White);

    updateScrollbar();
}

void ListView::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved) {
        ScreenPos mousePos(event.mouseMove.x, event.mouseMove.y);

        if (m_pressed) {
            moveScrollbar(mousePos.y);
        }

        return;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        m_scrollBar->setFillColor(sf::Color(0, 0, 0, 128));
        m_pressed = false;
        return;
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel != sf::Mouse::VerticalWheel) {
            return;
        }

        if (event.mouseWheelScroll.delta < 0) {
            setOffset(m_offset + 1);
        } else {
            setOffset(m_offset - 1);
        }
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
        m_scrollBar->setFillColor(sf::Color(128, 128, 128, 128));
        moveScrollbar(mousePos.y);
        m_pressed = true;
        return;
    }

    int index = (event.mouseButton.y - m_rect.y) / m_itemHeight + m_offset;

    if (index >= m_list.size()) {
        return;
    }

    if (index != m_currentItem) {
        m_currentItem = index;
        return;
    }

    if (std::filesystem::is_directory(m_list[m_currentItem])) {
        setCurrentPath(std::filesystem::canonical(m_list[m_currentItem]).string());
    }
}

void ListView::render(sf::RenderWindow *window)
{
    window->draw(*m_background);

    for (size_t i=0; i<m_texts.size(); i++) {
        if (i+m_offset >= m_list.size()) {
            continue;
        }

        if (std::filesystem::is_directory(m_list[i+m_offset])) {
            m_texts[i]->setFillColor(sf::Color::White);
        } else {
            m_texts[i]->setFillColor(sf::Color(128, 128, 128));
        }
    }

    if (m_currentItem - m_offset >= 0 && m_currentItem - m_offset < numVisible) {
        m_selectedOutline->setSize(Size(m_rect.width, m_itemHeight));
        m_selectedOutline->setPosition(ScreenPos(m_rect.x, m_rect.y + (m_currentItem - m_offset) * m_itemHeight));
        window->draw(*m_selectedOutline);

        m_texts[m_currentItem - m_offset]->setFillColor(sf::Color::Black);
    }

    for (std::unique_ptr<sf::Text> &text : m_texts) {
        window->draw(*text);
    }

    window->draw(*m_scrollBar);
}

void ListView::setCurrentPath(std::string pathString)
{
    if (pathString.empty()) {
        pathString = "/";
    }

    std::filesystem::path path(pathString);

    m_list.clear();

    hasDataFolder = false;
    try {

        // avoid crashing
        if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
            throw std::filesystem::filesystem_error("fuckings to boost which I blame for this shitty API", std::error_code());
        }

        std::filesystem::directory_iterator boostIsShit(path);
        for (std::filesystem::directory_entry entry : boostIsShit) try {
            const std::string entryName = entry.path().filename().string();
            if ((entryName == "Data" || entryName == "resources") && entry.is_directory()) {
                hasDataFolder = true;
            }

            m_list.push_back(entry.path().string());

            // MSVC and/or Wine has a troubled relationship with UTF-8 path names
        } catch (const std::exception &e) { WARN << "error adding dir entry, probably windows shit" << e.what(); }
    } catch (const std::filesystem::filesystem_error &err) {
        WARN << "Err" << err.what();
        if (m_currentPath.empty()) {
            WARN << "not even a current path, blame boost";
            return;
        }

        pathString = m_currentPath.string();
    }
    path = std::filesystem::path(pathString);

    if (!path.parent_path().empty() && pathString != path.parent_path()) {
        std::filesystem::path dotdot = pathString;
        dotdot += "/..";
        m_list.push_back(dotdot.string());
    }

    std::sort(m_list.begin(), m_list.end(), [](const std::filesystem::path &a, const std::filesystem::path &b){
        const bool aIsDir = std::filesystem::is_directory(a);
        const bool bIsDir = std::filesystem::is_directory(b);
        if (aIsDir != bIsDir) {
            return !aIsDir < !bIsDir;
        }

        const std::string aName = util::toLowercase(a.filename().string());
        const std::string bName = util::toLowercase(b.filename().string());
        const bool aDot = aName[0] == '.' && (aName.size() < 2 || aName[1] != '.');
        const bool bDot = bName[0] == '.' && (bName.size() < 2 || bName[1] != '.');
        if (aDot != bDot) {
            return aDot < bDot;
        }

        return a.filename() < b.filename();
    });

    m_currentItem = 0;
    m_offset = 0;

    for (size_t i=0; i<m_texts.size(); i++) {
        if (i < m_list.size()) {
            std::string filename = std::filesystem::path(m_list[i]).filename().string();
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

    m_currentPath = pathString;
}

void ListView::setOffset(int offset)
{
    if (offset > int(m_list.size()) - numVisible) {
        offset = int(m_list.size()) - numVisible;
    }

    if (offset < 0) {
        offset = 0;
    }

    if (offset == m_offset) {
        return;
    }

    m_offset = offset;

    for (size_t i=0; i<m_texts.size(); i++) {
        if (i+m_offset < m_list.size()) {
            std::string filename = std::filesystem::path(m_list[i+m_offset]).filename().string();
            if (filename.size() > 40) {
                filename.resize(40);
                filename += "...";
            }
            if (std::filesystem::is_directory(m_list[i+m_offset])) {
                m_texts[i]->setString("[" + filename + "]");
                m_texts[i]->setFillColor(sf::Color(192, 192, 192));
            } else{
                m_texts[i]->setFillColor(sf::Color(192, 192, 192));
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
    return std::filesystem::canonical(m_currentPath).string();
}

void ListView::updateScrollbar() const
{
    if (m_list.empty()) {
        m_scrollBar->setSize(Size(0, 0));
        return;
    }

    float scrollbarSize =  m_rect.height * (float(numVisible) / m_list.size());
    float width = 20;
    if (scrollbarSize >= m_rect.height) {
        m_scrollBar->setSize(Size(0, 0));
        return;
    }

    scrollbarSize = std::max(scrollbarSize, 10.f);
    m_scrollBar->setSize(Size(width, scrollbarSize));

    int scrollbarPos = m_rect.height * float(m_offset) / m_list.size();
    m_scrollBar->setPosition(m_rect.topRight() + ScreenPos(-20, scrollbarPos));
}

void ListView::moveScrollbar(int mouseY)
{
    float ratio = (mouseY - m_scrollBar->getSize().y/2 - m_rect.y) / m_rect.height;
    setOffset(m_list.size() * ratio);
}
