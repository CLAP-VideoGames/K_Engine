testScene = {
    changeSceneButton = {
        Transform = {
            position = " -0.500000 ,-0.500000 ,-0.000000 ",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "Boton"
            imageName = "DefaultButton"
            hovermageName = "TestButtonAmongus"
            pressedImageName = "ButtonApretado"
            onClick = function(){
                sceneManager:changeScene("map")
            }
        }
    }
}