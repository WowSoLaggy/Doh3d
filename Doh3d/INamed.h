#pragma once


namespace Doh3d
{

class INamed
{
public:

  virtual std::string& getName() { return d_name; }
  virtual const std::string& getName() const { return d_name; }

  virtual void setName(const std::string& i_name) { d_name = i_name; }

protected:

  std::string d_name;
};

} // ns Doh3d
