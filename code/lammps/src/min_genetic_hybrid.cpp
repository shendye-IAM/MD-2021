#include "min_genetic_hybrid.h"
#include "min_cg.h"
#include "style_integrate.h"  // IWYU pragma: keep
#include "style_minimize.h"   // IWYU pragma: keep
#include "update.h"
#include "output.h"
#include "error.h"
#include <cmath>
#include <cstring>

/* ---------------------------------------------------------------------- */

LAMMPS_NS::MinGeneticHybrid::MinGeneticHybrid(LAMMPS *lmp) : MinGeneticParent(lmp)
{
  minimize = nullptr;
  minimize_style = nullptr;

  minimize_map = new MinimizeCreatorMap();

  #define MINIMIZE_CLASS
  #define MinimizeStyle(key,Class) \
    (*minimize_map)[#key] = &ga_minimize_creator<Class>;
  #include "style_minimize.h"    // IWYU pragma: keep
  #undef MinimizeStyle
  #undef MINIMIZE_CLASS

  char *str;
  str = (char *) "cg";
  create_minimize(1,&str,1);
}

LAMMPS_NS::MinGeneticHybrid::~MinGeneticHybrid()
{
  delete [] minimize_style;
  delete minimize;

  delete minimize_map;
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGeneticHybrid::init()
{
    Min::init();
    minimize->init();
    
    dt = update->dt;
    last_negative = update->ntimestep;
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGeneticHybrid::ga_setup()
{
  //needed for cg
    minimize->setup();
}

/* ---------------------------------------------------------------------- */

void LAMMPS_NS::MinGeneticHybrid::CalculateFitness(Population &population) {

  //settings lammps atom positions to chromosomes
  for (int i = elites; i < population.numIndividuals; i++) {
    for (int j = 0; j < nvec; j++) {
      xvec[j] = population.individuals[i].chromosome[j];
    }

    ecurrent = energy_force(0);
    neval++;

    if (!isinf(ecurrent)) {
      localMinimization();
    }
    population.individuals[i].SetFitness(ecurrent);
    population.individuals[i].SetChromosome(xvec);
  }
}

void LAMMPS_NS::MinGeneticHybrid::localMinimization() 
{
  bigint ntimestep_curr = update->ntimestep;
  bigint next_ = output->next;

  //disabling output for local cg optimization
  output->next = -1;

  //performing local cg optimization
  minimize->iterate(localMinSteps);
  update->ntimestep = ntimestep_curr;

  output->next = next_;
  ecurrent = energy_force(0);
  neval++;
}

/* ----------------------------------------------------------------------
   Code for local minimizer
------------------------------------------------------------------------- */

void LAMMPS_NS::MinGeneticHybrid::create_minimize(int narg, char **arg, int trysuffix)
{
  if (narg < 1) error->all(FLERR,"Illegal run_style command");

  delete [] minimize_style;
  delete minimize;

  int sflag;
  new_minimize(arg[0],narg-1,&arg[1],trysuffix,sflag);

  std::string estyle = arg[0];
  if (sflag) {
    estyle += "/";
    if (sflag == 1) estyle += lmp->suffix;
    else estyle += lmp->suffix2;
  }
  minimize_style = utils::strdup(estyle);
}

/* ----------------------------------------------------------------------
   create the Minimize style, first with suffix appended
------------------------------------------------------------------------- */

void LAMMPS_NS::MinGeneticHybrid::new_minimize(char *style, int /* narg */, char ** /* arg */,
                           int trysuffix, int &sflag)
{
  if (trysuffix && lmp->suffix_enable) {
    if (lmp->suffix) {
      sflag = 1;
      std::string estyle = style + std::string("/") + lmp->suffix;
      if (minimize_map->find(estyle) != minimize_map->end()) {
        MinimizeCreator &ga_minimize_creator = (*minimize_map)[estyle];
        minimize = ga_minimize_creator(lmp);
        return;
      }
    }

    if (lmp->suffix2) {
      sflag = 2;
      std::string estyle = style + std::string("/") + lmp->suffix2;
      if (minimize_map->find(estyle) != minimize_map->end()) {
        MinimizeCreator &ga_minimize_creator = (*minimize_map)[estyle];
        minimize = ga_minimize_creator(lmp);
        return;
      }
    }
  }

  sflag = 0;
  if (minimize_map->find(style) != minimize_map->end()) {
    MinimizeCreator &ga_minimize_creator = (*minimize_map)[style];
    minimize = ga_minimize_creator(lmp);
    return;
  }

  error->all(FLERR,"Illegal minimize style");
}

/* ----------------------------------------------------------------------
   one instance per minimize style in style_minimize.h
------------------------------------------------------------------------- */

template <typename T>
LAMMPS_NS::Min *LAMMPS_NS::MinGeneticHybrid::ga_minimize_creator(LAMMPS *lmp)
{
  return new T(lmp);
}
