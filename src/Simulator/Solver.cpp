
#include "ISolver.h"
#include "../Utils/math.h"


#define tofloat(x)  (static_cast<float>(x))


namespace fck
{
    //Solver::Solver(int _count, float _dt) :count(_count), dt(_dt)
    //{
    //    vp = move(vector<Particle>(count));
    //    assert(vp.size());

    //    originDistrib.x = 10;
    //    originDistrib.y = 20;
    //    originDistrib.z = 10;

    //    griddim.x = 20;
    //    griddim.y = 20;
    //    griddim.z = 20;

    //    grid = move(Grid(griddim.x*griddim.y*griddim.z));

    //    InitParticle();
    //}


    //Solver::~Solver()
    //{
    //    delete init;
    //    delete boundary;
    //}


    //void Solver::InitParticle()
    //{
    //    init->initialize();
    //    /*unsigned int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    //    mt19937 gen(seed);
    //    uniform_int_distribution<int> distrib(-100, 100);
    //    int id = 0;
    //    for (auto& particle : vp)
    //    {
    //        particle.id = id;
    //        particle.dens = 0.0f;
    //        particle.pres = 0.0f;
    //        particle.force = vec3f(0.0f, 0.0f, 0.0f);
    //        particle.vel = vec3f(0.0f, 0.0f, 0.0f);
    //        particle.mass = 1.0f;

    //        int y = id / (originDistrib.x * originDistrib.z);
    //        int z = (id - y * originDistrib.x * originDistrib.z) / originDistrib.z;
    //        int x = id % originDistrib.x;


    //        particle.pos.x = 0.5f + x * 1.0f + tofloat(distrib(gen)) / 500.0f;
    //        particle.pos.y = 0.5f + y * 1.0f + tofloat(distrib(gen)) / 500.0f;
    //        particle.pos.z = 0.5f + z * 1.0f + tofloat(distrib(gen)) / 500.0f;
    //        id++;
    //    }*/
    //}

    //int Solver::CalcGridIndex(const Pos& pos) const
    //{
    //    int gridx = pos.x / 1.0f;
    //    int gridy = pos.y / 1.0f;
    //    int gridz = pos.z / 1.0f;

    //    return gridx + gridz * griddim.x + gridy * griddim.x*griddim.z;
    //}

    //void Solver::FillGrid()
    //{
    //    int gridindex = 0;
    //    for (const Particle & cp : vp)
    //    {
    //        gridindex = CalcGridIndex(cp.pos);
    //        assert(gridindex < griddim.x*griddim.y*griddim.z);
    //        grid[gridindex].push_back(cp.id);
    //    }
    //}


    //void Solver::FillNeighbour()
    //{
    //    int currentGridIndex = 0;
    //    for (auto& cp : vp)
    //    {
    //        int i, j, k;
    //        int gridx = cp.pos.x / 1.0f;
    //        int gridy = cp.pos.y / 1.0f;
    //        int gridz = cp.pos.z / 1.0f;

    //        for (i = -1; i <= 1; i++)
    //        {
    //            for (j = -1; j <= 1; j++)
    //            {
    //                for (k = -1; k <= 1; k++)
    //                {
    //                    currentGridIndex = (gridx + i) + (gridz + k)*griddim.x + (gridy + j)*griddim.x*griddim.z;

    //                    if (currentGridIndex < (griddim.x*griddim.y*griddim.z) && currentGridIndex >= 0)
    //                    {
    //                        auto& cell = grid[currentGridIndex];
    //                        for_each(begin(cell), end(cell), [&](int x) {if ((cp.pos - vp[x].pos).norm() < para.h) { cp.ngbour.push_back(x); } });
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}


    //float Poly6Kernel(vec3f r, float h)
    //{
    //    return 315.0f / (64.0f * math::PI<float> * math::pow9(h)) * math::cube(math::square(h) - r * r);
    //}


    //vec3f kernel_grident(vec3f r, float h)
    //{
    //    return -945.0f / (32.0f * math::PI<float> * math::pow9(h)) * math::square(math::square(h) - r * r) * r;
    //}


    //float laplacian_kernel(vec3f r, float h)
    //{
    //    return 45.0f / (math::PI<float> * math::pow6(h)) * (h - sqrtf(r.x*r.x + r.y*r.y + r.z*r.z));
    //}


    //void Solver::CalcDens()
    //{
    //    for (auto& particle : vp)
    //    {
    //        particle.dens = accumulate(begin(particle.ngbour), end(particle.ngbour), 0.0f, [&](float x, int j)->float {return x + particle.mass*Poly6Kernel(particle.pos - vp[j].pos, para.h); });
    //    }
    //}

    //void Solver::CalcPressure()
    //{
    //    for_each(begin(vp), end(vp), [](Particle& p) {p.pres = para.k*(p.dens - para.restDens); });

    //    /*
    //    ofstream outPres("pressure.txt");
    //    ostream_iterator<Particle> out(outPres, "\n");
    //    copy(begin(vp), end(vp), out);
    //    */
    //}

    //void Solver::CalcForce()
    //{
    //    for (auto& cp : vp)
    //    {
    //        cp.force = accumulate(begin(cp.ngbour), end(cp.ngbour), vec3f(0.0f, 0.0f, 0.0f),
    //            [&](vec3f init, int index)
    //        {
    //            return init + (-vp[index].mass*(cp.pres + vp[index].pres) / (2.0f*vp[index].dens)*kernel_grident(cp.pos - vp[index].pos, para.h));
    //        });

    //        cp.force = accumulate(begin(cp.ngbour), end(cp.ngbour), cp.force,
    //            [&](vec3f init, int index)
    //        {
    //            return init + para.v*vp[index].mass*(vp[index].vel - cp.vel) / vp[index].dens*laplacian_kernel(cp.pos - vp[index].pos, para.h);
    //        });

    //        cp.force += para.gravity;
    //    }

    //    /*
    //    ofstream outForce("force.txt");
    //    ostream_iterator<Particle> out(outForce, "\n");
    //    copy(begin(vp), end(vp), out);
    //    */
    //}

    //struct UpdateVel
    //{
    //    UpdateVel(float _dt) :dt(_dt)
    //    { }

    //    void operator()(Particle& p)
    //    {
    //        p.vel += p.force*dt;
    //    }

    //    float dt;
    //};

    //struct FindMax
    //{
    //    FindMax(float _maxVal) :maxValue(_maxVal)
    //    { }
    //    void operator()(Particle& p)
    //    {
    //        float temp = p.vel.norm();
    //        if (temp > maxValue)
    //        {
    //            maxValue = temp;
    //        }
    //    }
    //    float maxValue;
    //};

    //struct UpdatePos
    //{
    //    UpdatePos(float _dt) :dt(_dt)
    //    { }

    //    void operator()(Particle& p)
    //    {
    //        p.pos += p.vel*dt;
    //    }

    //    float dt;
    //};

    //void Solver::UpdateVelAndPos()
    //{
    //    for_each(begin(vp), end(vp), UpdateVel(dt));
    //    FindMax FM(0.0f);
    //    FM = for_each(begin(vp), end(vp), FM);

    //    for_each(begin(vp), end(vp), UpdatePos(FM.maxValue));

    //    /*
    //    ofstream outVelAndPos("velAndPos.txt");
    //    ostream_iterator<Particle> out(outVelAndPos, "\n");
    //    copy(begin(vp), end(vp), out);
    //    */
    //}



    ///*
    //struct Handle
    //{
    //    Handle(const tuple6& _t) :t(_t)
    //    { }

    //    void operator()(Particle& p)
    //    {
    //        Pos &pos = p.pos;
    //        Vel &vel = p.vel;

    //        (pos.x < t.xmin + 0.5) ? pos.x = t.xmin + 0.5, vel.x = -vel.x : 1;
    //        (pos.x > t.xmax - 0.5) ? pos.x = t.xmax - 0.5, vel.x = -vel.x : 1;

    //        (pos.y < t.ymin + 0.5) ? pos.y = t.ymin + 0.5, vel.y = -vel.y : 1;
    //        (pos.y > t.ymax - 0.5) ? pos.y = t.ymax - 0.5, vel.y = -vel.y : 1;

    //        (pos.z < t.zmin + 0.5) ? pos.z = t.zmin + 0.5, vel.z = -vel.z : 1;
    //        (pos.z > t.zmax - 0.5) ? pos.z = t.zmax - 0.5, vel.z = -vel.z : 1;
    //    }

    //    const tuple6 t;
    //};
    //*/

    //void Solver::HandleBoundary()
    //{
    //    for_each(begin(vp), end(vp), Handle(bound));
    //}

    //void Solver::ClearGrid()
    //{
    //    for_each(begin(grid), end(grid), [&](Cell& cell) {cell.clear(); });
    //}

    //void Solver::ClearNeigh()
    //{
    //    for_each(begin(vp), end(vp), [&](Particle& p) {p.ngbour.clear(); });
    //}

    //void Solver::Simulate()
    //{
    //    FillGrid();
    //    FillNeighbour();
    //    CalcDens();
    //    CalcPressure();
    //    CalcForce();
    //    UpdateVelAndPos();
    //    HandleBoundary();
    //    ClearGrid();
    //    ClearNeigh();
    //}
}
