scene = {
    cubo = {
        Transform = {
            position = {  -3.500000 ,1.500000 ,-0.000000 },
            rotation = {  0.923880 ,-0.000000 ,0.000000 ,-0.382683 },
            scale = {  1.000000 ,1.000000 ,1.000000 },
        },
        GameObjectType = {
            Character
        },
        RigidBody = {
            Type = Dynamic,
            Collider = Box,
            Mass = 1.0,
            isTrigger = false
        },
        MeshRenderer = {
            MeshFile = "cubo.mesh",
        }
    },
    suelo = {
        Transform = {
            position = {  -3.500000 ,-0.500000 ,0.000000 },
            rotation = {  0.923880 ,-0.000000 ,0.000000 ,-0.382683 },
            scale = {  1.000000 ,1.000000 ,1.000000 },
        },
        GameObjectType = {
            Map
        },
        RigidBody = {
            Type = Static,
             Collider = Box,
             Mass = 1.0,
             isTrigger = false
        },
        MeshRenderer = {
            MeshFile = "suelo.mesh",
        }
    },
    detalle = {
        Transform = {
            position = {  -2.322678 ,0.085155 ,0.000000 },
            rotation = {  0.923880 ,-0.000000 ,0.000000 ,-0.382683 },
            scale = {  1.000000 ,1.000000 ,1.000000 },
        },
        GameObjectType = {
            Map
        },
        RigidBody = {
            Type = Static,
             Collider = Box,
             Mass = 1.0,
             isTrigger = false
        },
        MeshRenderer = {
            MeshFile = "detalle.mesh",
        }
    },
}

entities = {"cubo" ,"suelo" ,"detalle" }

