namespace rmm::rtoolbox {

Window::Window(Window::Description&& description)
  : oPtr{ std::make_unique<Window_Implementation>(std::move(description)) }
{
}

Window::~Window() {}

void
Window::Hide() const
{
  oPtr->Hide();
}

void
Window::Show() const
{
  oPtr->Show();
}

void Window::Run() const
{
  oPtr->Run();
}

void*
Window::GetHandle() const noexcept
{
  return oPtr->GetHandle();
}

void Window::SetIcon(ResourceID icon) const noexcept
{
  oPtr->SetIcon(icon);
}

} // namespace rmm::rtoolbox
