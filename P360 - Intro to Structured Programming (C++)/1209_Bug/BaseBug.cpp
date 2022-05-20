#include "BaseBug.h"

BaseBug::BaseBug(string cn, string tx, string od, string de) {
  _commonName = cn;
  _taxonomy = tx;
  _order = od;
  _description = de;
}

string BaseBug::GetString() const {
  return "\n\nBug Information"
         "\n  Common Name....: " + _commonName +
         "\n  Taxonomic Name.:" + _taxonomy +
         "\n  Order..........: " + _order +
         "\n  Description....: " + _description + "\n";
}