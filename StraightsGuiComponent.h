#ifndef STRAIGHTS_GUI_COMPONENT
#define STRAIGHTS_GUI_COMPONENT

class Command;

class StraightsGuiComponent {
  private:
    StraightsGuiComponent *parent_;

  public:
    explicit StraightsGuiComponent(StraightsGuiComponent *parent = nullptr);
    virtual void executeCommand(Command);
};

#endif
