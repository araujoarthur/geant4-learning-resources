/*
    A detector is made of a number of VOLUMES.

    The largest volume is called World and contains with some margin, all other volumes
    in the detector geometry.

    Other volumes are created and placed inside previous volumes, included in the World volume.

    Simplest and most efficient description of World is a box.

    A volume is created by describing its shape and its physical characteristics, and then placing it
    inside a containing volume (the created volume is called daughter volume, the containing volume is called mother volume).
    The daughter uses the mother as coordinate system (FoR).

    The volume's shape is described using the concept of a SOLID (has a shape and
    specific values for each of that shape's dimensions): A rectangle of base sides of 10 and height of 20 is a solid, for example.

    A LOGICAL VOLUME is used to describe a volume's full properties. It includes the geometrical properties of the solid, and adds physical
    characteristics (material, whether it contains any sensitive detector elements, the EM field, etc)

    a PHYSICAL VOLUME is used to describe the position of a volume (the physical volume places a copy of the logical volume inside a larger, containing, volume).
*/

/*
    To create a volume we need to:
     - Create a solid
     - Create a logical volume from that solid and add attributes to it.

    [Each of the volume types (solid, logical, and physical) has an associated registry (VolumeStore) which contains a list
    of all the objects of that type constructed so far] (sounds important.)

*/

// Example Creating a Box:

// Define the extent of the SOLID in meters (each axis.)
G4double world_hx = 3.0*m; //Geant4 is unitful. More on that after.
G4double world_hy = 1.0*m;
G4double world_hz = 1.0*m;

G4Box* worldBox = new G4Box("World", world_hx, world_hy, world_hz);
// Created a box (of type G4Box*) called "World" that goes from -3.0m to 3.0m in Cartesian X,
// from -1.0m to 1.0m in Cartesian Y and from -1.0m to 1.0m in Cartesian Z.
// (G4Box take as argument the halves of the extents)

// Example Creating a Cylinder:

G4double innerRadius = 0.*cm;
G4double outerRadius = 60.*cm; //Full outer radius.
G4double hz = 25.*cm; // Half length in Z
G4double startAngle =0.*deg;
G4double spanningAngle = 360.*deg;

G4Tubs* trackerTube = new G4Tubs("Tracker", innerRadius, outerRadius, hz, startAngle, spanningAngle);

// Example Creating a Logical Volume:
// Creating a simple logical volume filled with argon gas using the box created before.

G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, Ar, "World"); //Ar is defined as constat?
// Created a logical volume called world and filled with Ar gas, from worldBox solid

// Creating a logical volume with the cylindrical solid filled with aluminium:
G4LogicalVolume *trackerLog = new G4LogicalVolume(trackerTube, Al, "Tracker");


// Placing a Volume by Creating a Physical Volume.

G4double pos_x = -1.0*meter;
G4double pos_y = 0.0*meter;
G4double pos_z = 0.0*meter;

// Effectively creating the physica volume:
G4VPhysicalVolume* trackerPhys = new G4PVPlacement(0, // Rotation (0 = no rotation)
                                                    G4ThreeVector(pos_x, pos_y, pos_z), // Position
                                                    trackerLog, // The logical volume
                                                    "Tracker", // Its name (Physical Volume's Name)
                                                    worldLog, // Its mother (LOGICAL) volume
                                                    false, // No boolean operations (?)
                                                    0). // Its copy number.

/*
    Places the logical volume trackerLog at the origin of the mother volume, shifted 1 meter in x-axis and unrotated.
    Resulted in a physical volume named tracker with copy number 0.

    There's just one exception to the rule that a physical object must be placed inside a mother volume: the World volume (the largest created that contain all other volumes.)
    
    The world must be created as a G4PVPlacement with a null mother pointer. It MUST be unrotated and MUST sit in the origin of the global coordinate system.
*/

/*
n GEANT4, the rotation matrix associated to a placed physical volume represents the rotation of the reference system of this volume with respect to its mother.
A rotation matrix is normally constructed as in CLHEP, by instantiating the identity matrix and then applying a rotation to it. This is also demonstrated in Example B3
*/

// SPECIFYING MATERIALS:
/*
    There are 3 main classes designed in geant (regarding materials): Material, Element and Isotope.

    Each of these classes has a table as a static data member, which is for keeping track of the instances created of the respective classes.
    All three objects automatically register themselves into the corresponding table on construction and should never be deleted in user code.

    --> G4Element describes the properties of ATOMS:
        atomic number
        number of nucleons
        atomic mass
        shell energy
        quantities as: cross sections per atom, etc.

    --> G4Material describes the macroscopic properties of matter:
        density
        state
        temperature
        pressure
        quantities as: radiation length, mean free path, dE/dx, etc.

        G4Material is the one visible to the toolkit and is used by the tracking, the geometry and the physics
        Contains all the information relative to the eventual elements and isotopes of which it is made.
*/

// Example Defining Material: Liquid Argon (specifying its name, density, mass per mole and atomic number)

G4double z, a, density;
density = 1.390*g/cm3;
a = 39.95*g/mole;

G4Material* lAr = new G4Material(name="liquidArgon", z=18., a, density);

//      then we can use the pointer lAr to specify the matter of a given logical volume

G4LogicalVolume* myLbox = new G4LogicalVolume(aBox, lar, "Lbox", 0,0,0);


// Example Defining a Molecule: H2O (specifying the number of atoms in the molecule)

G4double z, a, density;
G4String name, symbol;
G4int ncomponents, natoms; //Why define ncomponents if it is only assigned inside the constructor?

a = 1.01*g/mole;
G4Element* elH = new G4Element(name="Hydrogen", symbol="H", z=1., a);

a = 16.00*g/mole;
G4Element* elO = new G4Element(name="Oxygen", symbol="O", z=8., a);

density = 1.000*g/cm3;
G4Material* H2O = new G4Material(name="Water", density, ncomponents=2);

H2O->AddElement(elH, natoms=2);
H2O->AddElement(elO, natoms=1);

// Example Defining a Mixture by Fractional Mass: (air from Nitrogen and Oxygen giving fractional mass of each component)
G4double z,a, fractionmass, density;
G4String name, symbol;
G4int ncomponents;

a = 14.01*g/mole;
G4Element* elN = new G4Element(name="Nitrogen", symbol="N", z=7., a);

a = 16.00*g/mole;
G4Element* elO = new G4Element(name="Oxygen", symbol="O", z=8., a);

density = 1.290*mg/cm3;
G4Material* Air = new G4Material(name="Air", density, ncomponents=2);

Air->AdElement(elN, fractionmass=70*perCent);
Air->AddElement(elO, fractionmass=30*perCent);

// Example Defining a Material from Geant4 Material Database (Air and Water accessed via G4 Mat DB)
G4NistManager* man = G4NistManager::Instance();

G4Material* H2O = man->FindOrBuildMaterial("G4_WATER");
G4Material* Air = man->FindOrBuildMaterial("G4_AIR")

// Example Defining a MAterial from the Base Material (water with unusual density)
/*
    It is possible to build new materials on base of the ones that already exist.
*/

G4double density;

density = 1.05*mg/cm3;
G4Material* water1 = new G4Material("Water_1.05", density, "G4_WATER");

density = 1.03*mg/cm3;
G4NistManager* man = G4NistManager::Instance();
G4Material* water2 = man->BuildMaterialWithNewDensity("Water_1.03", "G4_WATER", density);


// SPECIFYING PARTICLES

/*
    G4VUserPhysicsList is one of the mandatory user base classes shown in chapter2.cc. Within this class, all particles and physics processes to be used
    in the simulation must be defined. The range cut-off parameter should also be defined in this class.

    To specify particles, the user needs to create a class derived from G4VuserPhysicsList and implement these 2 pure virtual methods (Check C++ Reference)
        ConstructParticle(); --> Construction or Particles
        ConstructProcess(); --> Construct processes and register them to particles

    It is possible to override SetCuts() to set a range cut value for all particles.
*/

// Particle Definition:

/*
    Particles provided By Geant4 for use in simulations:
        Ordinary Particles (electrons, protons, gammas),
        Resonant Particles with very short lifetimes (vector mesons, delta baryons),
        Nuclei (deuteron, alpha, and heavy ions including hyper-nuclei),
        quarks, di-quarks and gluon
    
    Each particle is represented by its own class, which is derived from G4ParticleDefinition (Except G4Ions that represents all heavy nucleis)
    There are six major categories:
        lepton
        meson
        baryon
        shortlived
        ion
    
    Each of which is defined in a corresponding sub-directory under geant4/source/particles. There is also a corresponding granular library for each particle category

    ------

    The G4ParticleDefinition Class:

    It has properties which characterize individual particles such as:
        name
        mass
        charge
        spin
        ...
    Most of those are read-only. G4ParticlePropertyTable is used to retrieve particle property of G4ParticleDefinition
    into (from) G4ParticlePropertyData (???)
    
    -----

    How to Access a Particle:

    Each particle class type representes an individual particle type and each class has a SINGLE object. This object can
    be accessed by using the static method of each class. [THERE ARE EXCEPTIONS FOR THIS RULE.]

    FOR EXAMPLE: G4Electron represents the electron and the member G4Electron::theInstance points to its ONLY object. The pointer to this object
    is available through the static methods:
        G4Electron::ElectronDefinition().G4Electron::Definition() (Two Methods or one?)
    
    >>> The unique object for each particle class is created when its static method to get the pointer is called at the first time.
    
    [!!] Because particles are dynamic objects and should be instantiated before initialization of physics processes, you must
    explicitly invoke static methods of all particle classes required by your program at the initialization step.
*/  

// Dictionary of Particles:
/*
    G4ParticleTable class is provided as a dictionary of particles with utility methods provided, like:
        FindParticle(G4string name); --> find particle by name
        FindParticle(G4int PDGencoding); --> Find particle by PDG encoding
    
    G4ParticleTable is a singleton object (Check C++ Reference!) and the static method G4ParticleTable::GetParticleTable() provides its pointer.

    For heavy ions (including hyper-nuclei), objects are created dynamically by requests from users and processes.
    The G4ParticleTable class provides methods to create ions such as:
*/

G4ParticleDefinition* GetIon( G4int atomicNumber,
                            G4int atomicMass,
                            G4double excitationEnergy);

// Material information can be printed:
// For a single material: G4cout << H2O;
// A list of materials: G4cout << *(G4Material::GetMaterialTable());

/*
    Final Question:
    What is a copy number?
    does world have a physical volume?
    Why is z a double?
    What is range cut-off?
    What is a granular library?
*/