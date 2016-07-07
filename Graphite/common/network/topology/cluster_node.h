#ifndef CLUSTER_NODE_H
#define CLUSTER_NODE_H

#define CW   254
#define CCW  255

typedef struct 
{
    int _layer;
    int _wavelength;
    int _waveguide;
    int _direction; // 
} ReceivingCluster;

#endif // CLUSTER_NODE_H
