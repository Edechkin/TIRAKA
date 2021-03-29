// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <map>

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: Theta(1)
    // Short rationale for estimate: Se vaan on, pitää kaiketi kirjaa omasta koostaan.
    int place_count();

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Kutsuu jokaisen elementin purkajaa
    void clear_all();

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Käydään elementit läpi yksi kerrallaan.
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate: find ja insert molemmat keskimäärin vakioaikaisia ja huonoimmillaan lineaarisia. Ei luuppeja.
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate: Find keskimäärin vakioaikainen, huonoimmillaan lineaarinen ja at-funktioon pätee sama.
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate: Find ja at -funktiot keskimäärin vakioaikaisia, huonoimmillaan lineaarisia.
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: sort-funktion kompleksisuus
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: sort-funktion kompleksisuus
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Käydään places_-rakennette elementti kerrallaan läpi
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Käydään places_-rakennette elementti kerrallaan läpi
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate: Find ja at -funktiot keskimäärin vakioaikaisia, huonoimmillaan lineaarisia
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate: Find ja at -funktiot keskimäärin vakioaikaisia, huonoimmillaan lineaarisia
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate:Find ja Insert -funktiot keskimäärin vakioaikaisia, huonoimmillaan lineaarisia
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate: Find ja at -funktiot keskimäärin vakioaikaisia, huonoimmillaan lineaarisia
    Name get_area_name(AreaID id);

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate: Find ja at -funktiot keskimäärin vakioaikaisia, huonoimmillaan lineaarisia
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Käydään areas_-rakenne läpi elementti kerrallaan
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(n), keskimäärin Theta(1)
    // Short rationale for estimate: Find ja at -funktiot keskimäärin vakioaikaisia, huonoimmillaan lineaarisia
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Rekursiivisen funktion kutsujen määrä riippuu alueen "ylialueiden" määrästä. Lisäksi at-funktio huonoimmillaan lineaarinen
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance: Theta(1)
    // Short rationale for estimate: Ei toteutusta
    void creation_finished();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Rekursiivisen funktion kutsujen määrä riippuu alialueiden määrästä. Find ja at huonoimillaan lineaarisia, alialuevekotreita käydöön elementti kerrallaan.
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: Vectorin sorttaus on O(n log(n)), sen lisäksi suoritetaan huonoimmillaan lineaarisia toimenpiteitä.
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: O(n), keksimäärin Theta(1)
    // Short rationale for estimate: Find, at ja erase kaikki keskimäärin vakioaikaisia, huonoimmillaan lineaarisia.
    bool remove_place(PlaceID id);

    // Estimate of performance:
    // Short rationale for estimate:
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

private:
    // Add stuff needed for your class implementation here
    struct place{
        Name name;
        PlaceType type;
        Coord xy;
    };
    std::unordered_map<PlaceID, struct place> places_;
    struct area{
        Name name;
        std::vector<Coord> coords;
        std::vector<AreaID> sub_areas;
        AreaID super_area;

    };
    std::unordered_map<AreaID, struct area> areas_;

    std::vector<AreaID> recursive_sub_area_in_areas(AreaID, std::vector<AreaID>&);

    std::vector<AreaID> recursive_all_sub_areas_in_area(AreaID, std::vector<AreaID>&);


};

#endif // DATASTRUCTURES_HH
