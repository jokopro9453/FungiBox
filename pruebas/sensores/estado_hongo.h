#ifndef ESTADO_H
#define ESTADO_H

class Hongo{
    public:
        Hongo();

        virtual ~Hongo();

        void regular_temp(float temp);
        void regular_hum(int hum);
        void vent(float temp, int hum);

    protected:
    
        float min_temp;
        float max_temp;   
        int min_hum;
        int max_hum;
        bool cama_calor = false;
        bool humidificador = false;
        bool ventilador = false;
};

class Incubacion: public Hongo {
    public:
        Incubacion();
};

class Induccion: public Hongo {
    public:
        Induccion();
};

class Fructificacion: public Hongo {
    public:
        Fructificacion();
};

#endif