using namespace std;

void Graphics::eventLoop()
{
    manager->startDetachedThread(&Graphics::textualGraphics, this);

    GraphicsInternals::openWindow(string("Sim"));

    //Menu numbers"
      // 0 - Pause
      // 1 - Game
    while (window.isOpen())
    {
        if (menu == 0) //paused
        {
            pauseMenu();
        }
        else if (menu == 1) //running the game
        {
            game();
        }
    }
}

void  Graphics::pauseMenu()
{
    //check window events
    sf::Event event;
    while (window.pollEvent(event))
    {
        GraphicsInternals::basicEvents(event); //Get window events

        //Pause control
        if (event.type == sf::Event::KeyPressed)
        {
          if (event.key.code == sf::Keyboard::Space)
          {
            if(manager->getPauseState()) //paused
              manager->resume();
            else
              manager->pause();

            menu = 1; //switch to the game menu
            return;
          }
        }

        //add click for menu options
    }

    //still draw the hexes, but don't have the interactivity of the map
    window.clear();
    GraphicsInternals::drawMap();         //Hex grid
    GraphicsInternals::drawEntities();    //Entites
    GraphicsInternals::pauseOverlay();    //Graying screen
    window.display();
}

void Graphics::game()
{
    //check window events
    sf::Event event;
    while (window.pollEvent(event))
    {
      //Get window events
      GraphicsInternals::basicEvents(event);
      //get controls
      GraphicsInternals::controlledEvents(event);

      //Pause control
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Space)
        {
          if(manager->getPauseState()) //paused
            manager->resume();
          else
            manager->pause();

          menu = 0; //switch to the pause menu
          return;
        }
      }
    }
    //Keyboard, mouse, etc
    GraphicsInternals::input();

    //Actually Draw!
    window.clear();
    GraphicsInternals::drawMap();         //Hex grid
    GraphicsInternals::drawEntities();    //Entites
    window.display();
}

void Graphics::textualGraphics() const
{
    manager->sleep(1000000000); //Wait for window to open

    string spin = "|\\-/";
    while (window.isOpen())
    {
        for (int i = 0; i < 4; ++i)
        {
            //Build print statement
            ostringstream output;
            output << "Res: " << manager->getResolution();
            output << "; Speed: " << manager->getSpeed();
            output << "; Tick: " << manager->getTick();
            output << "; Day: " << float(manager->getTick())/(60.0*60.0*24.0);
            output << "; entCount: " << bin->count();
            output << " " << spin[i];
            output << "    ";

            //Print it
            cout << output.str();
            cout.flush();

            //Delay for the spinner
            manager->sleep(75000000);  //Spin lock hovered around 30%

            //Refreash/clear screen
            for (size_t t = 0; t < output.str().size(); ++t)
                cout << "\b"; //clear last character
        }
    }
}
