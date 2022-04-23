scene = {
    cubo = {
        Transform = {
            position = " 0.000000 ,-0.500000 ,-0.000000 ",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        RigidBody = {
            Type = "Static" ,
            Collider = "Box" ,
            Mass = "0.0" ,
            Dimensions = "10,  2.4,  10",
            isTrigger = "false" ,
            isEnabled = "true"
        },
        Enabled = "true",
        MeshRenderer = {
            MeshFile = "cubo.mesh",
        }
    },
    originalPieceMap = {
        Transform = {
            position = " -0.269432 ,0.727520 ,0.000000 ",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        RigidBody = {
            Type = "Dynamic" ,
            Collider = "Box" ,
            Mass = "1.0" ,
            Dimensions = "1,  1,  1",
            isTrigger = "false" ,
            isEnabled = "true"
        },
        Enabled = "true",
        MeshRenderer = {
            MeshFile = "pieceMap.mesh",
        }
    },
    pieceMap_001 = {
        Transform = {
            position = " 0.679943 ,1.571774 ,0.000000 ",
            rotation = " 0 ,0 ,-25.976715 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        RigidBody = {
            Type = "Dynamic" ,
            Collider = "Box" ,
            Mass = "1.0" ,
            Dimensions = "1,  1,  1",
            isTrigger = "false" ,
            isEnabled = "true"
        },
        Enabled = "true",
        MeshRenderer = {
            MeshFile = "pieceMap.mesh",
            Material = "grass",
        }
    },
    pieceMap_002 = {
        Transform = {
            position = " -0.268904 ,2.678121 ,-0.412959 ",
            rotation = " -22.582804 ,33.304256 ,-37.142292 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        RigidBody = {
            Type = "Dynamic" ,
            Collider = "Box" ,
            Mass = "1.0" ,
            Dimensions = "1,  1,  1",
            isTrigger = "false" ,
            isEnabled = "true"
        },
        Enabled = "true",
        MeshRenderer = {
            MeshFile = "pieceMap.mesh",
            Material = "black",
        }
    },
    originalSphere = {
        Transform = {
            position = " -3.787061 ,2.838940 ,0.680828 ",
            rotation = " -22.582804 ,33.304256 ,-37.142292 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        RigidBody = {
            Type = "Dynamic" ,
            Collider = "Sphere" ,
            Mass = "1.0" ,
            Dimensions = "1,  1,  1",
            isTrigger = "false" ,
            isEnabled = "true"
        },
        Enabled = "true",
        MeshRenderer = {
            MeshFile = "ball.mesh",
        }
    },
    platform = {
        Transform = {
            position = " -5.046125 ,2.160827 ,0.000000 ",
            rotation = " 0 ,0 ,-28.46651 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        RigidBody = {
            Type = "Static" ,
            Collider = "Box" ,
            Mass = "0.0" ,
            Dimensions = "3.63,  1,  3.72",
            isTrigger = "false" ,
            isEnabled = "true"
        },
        Enabled = "true",
        MeshRenderer = {
            MeshFile = "platform.mesh",
        }
    },
    sphere_001 = {
        Transform = {
            position = " -5.564610 ,4.872576 ,0.967044 ",
            rotation = " -22.582804 ,33.304256 ,-37.142292 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        RigidBody = {
            Type = "Dynamic" ,
            Collider = "Sphere" ,
            Mass = "1.0" ,
            Dimensions = "1,  1,  1",
            isTrigger = "false" ,
            isEnabled = "true"
        },
        Enabled = "true",
        MeshRenderer = {
            MeshFile = "ball.mesh",
            Material = "grass",
        }
    },
    sphere_002 = {
        Transform = {
            position = " -4.013021 ,4.872576 ,-1.262424 ",
            rotation = " -22.582804 ,33.304256 ,-37.142292 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        RigidBody = {
            Type = "Dynamic" ,
            Collider = "Sphere" ,
            Mass = "6.0" ,
            Dimensions = "1,  1,  1",
            isTrigger = "false" ,
            isEnabled = "true"
        },
        Enabled = "true",
        MeshRenderer = {
            MeshFile = "ball.mesh",
            Material = "black",
        }
    },
}

entities = {"cubo" ,"originalPieceMap" ,"pieceMap_001" ,"pieceMap_002" ,"originalSphere" ,"platform" ,"sphere_001" ,"sphere_002" }

