testScene = {
    changeSceneButton = {
        Transform = {
            position = " -0.500000 ,-0.500000 ,-0.000000 ",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "Boton",
            imageName = "DefaultButton",
            hoverImageName = "TestButtonAmongus",
            pressedImageName = "ButtonApretado",
            onClick = "changeScene"
        }
    },
}

function changeScene()
    local logMan = LogManager.getInstance();
    logMan:printLog(2,"a  VeR  Si Me MuErO");
end

entities = { "changeSceneButton"}