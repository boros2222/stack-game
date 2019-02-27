#ifndef NEHEZSEG_H
#define NEHEZSEG_H

// Nehézség opciók
typedef enum {
    konnyu_v,kozepes_v,nehez_v,marad_v,rossz_gomb2
} nehezseg_opcio;

nehezseg_opcio nehezseg(void);

#endif // NEHEZSEG_H
