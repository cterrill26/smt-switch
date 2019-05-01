#ifndef SMT_SORT_H
#define SMT_SORT_H

#include <array>
#include <memory>
#include <string>

// Sort needs to have arguments
//  could be integers or other sorts
//  should use an enum for the different kinds of sorts probably

namespace smt
{
  // TODO : add other smt kinds
  enum Kind
  {
   ARRAY=0,
   BOOL,
   BV,
   INT,
   REAL,
   UNINTERPRETED,
   /** IMPORTANT: This must stay at the bottom.
                  It's only use is for sizing the kind2str array
   */
   NUM_KINDS
  };

  /**
     This function should only be called once, to generate the constexpr
     kind2str for converting enums to string_views.
  */
  constexpr std::array<std::string_view, NUM_KINDS> generate_kind2str()
    {
      std::array<std::string_view, NUM_KINDS> kind2str;
      kind2str[ARRAY] = std::string_view("ARRAY");
      kind2str[BOOL] = std::string_view("BOOL");
      kind2str[BV] = std::string_view("BV");
      kind2str[INT] = std::string_view("INT");
      kind2str[REAL] = std::string_view("REAL");
      kind2str[UNINTERPRETED] = std::string_view("UNINTERPRETED");
      return kind2str;
    }

  constexpr std::array<std::string_view, NUM_KINDS> kind2str = generate_kind2str();

  /**
     Abstract base class for representing an SMT sort.
     It holds a kind enum and any necessary data for that particular sort.

     Sort objects should never be constructed directly, but instead provided
     by a Solver.
   */
  class AbsSort
  {
  public:
    AbsSort(Kind t) : kind(t) {};
    virtual ~AbsSort() {};
    virtual std::string to_string() const = 0;
    bool is_array() const { return kind == ARRAY; };
    bool is_bool() const { return kind == BOOL; };
    bool is_bv() const { return kind == BV; };
    bool is_int() const { return kind == INT; };
    bool is_real() const { return kind == REAL; };
    // TODO: decide on exception or special value for incorrect usage
    virtual unsigned int get_width() const = 0;
    virtual unsigned int get_indexsort() const = 0;
    virtual unsigned int get_elemsort() const = 0;
    Kind get_kind() const { return kind; };
  protected:
    Kind kind;
  };

  using Sort = std::shared_ptr<AbsSort>;

}

#endif
