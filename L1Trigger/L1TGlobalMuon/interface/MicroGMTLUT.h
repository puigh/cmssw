#ifndef __l1microgmtlut_h
#define __l1microgmtlut_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <vector>

#include "../interface/MicroGMTConfiguration.h"

namespace l1t {
  class MicroGMTLUT {
    public:
      MicroGMTLUT() : m_totalInWidth(0), m_outWidth(0), m_initialized(false) {};
      virtual ~MicroGMTLUT() {};

      // should be implemented in each daughter!
      // This function is the minimum that should be provided
      int lookupPacked(int input) const;

      // These functions transform their inputs into the hashed input via the
      // hashInput function and use the lookupPacked function.
      // Instance -> which content is referred to
      virtual int lookup(const std::vector<PortType>& inputset) const;
      virtual void lookup(const std::vector<std::vector<PortType> >& inputsets, std::vector<int>& outputs) const;
      
      // populates the m_contents map.
      void initialize();

      // I/O functions
      void save(std::ofstream& output);
      void load(const std::string& inFileName);
      // solely for debugging: prints the LUT to cout
      void print();
      void contentsToStream(std::stringstream& stream);
      void headerToStream(std::stringstream& stream) const;

    protected:
      size_t m_totalInWidth;
      size_t m_outWidth;
      std::vector<input_t> m_inputs;
      std::map<int, int> m_contents;
      std::string m_fname;
      bool m_initialized;
  };
}

#endif /* defined(__l1microgmtlut_h) */