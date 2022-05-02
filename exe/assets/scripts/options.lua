options = {
    sliderVolume = {
        Transform = {
            position = "0.2, 0.6, 60",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Slider = {
            overlayName = "SliderVolumen",
            imageName = "DefaultButton",
            width = "0.4",
            height = "0.1",
            onSliderClick = "setMasterVolume"
        }
    },
    popSceneButton = {
        Transform = {
            position = "0.6, 0.2, 0",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Button = {
            overlayName = "PopScene",
            imageName = "DefaultButton",
            hoverImageName = "TestButtonAmongus",
            pressedImageName = "ButtonApretado",
            width = "0.3",
            height = "0.2",
            onClick = "popScene"
        }
    },
    focusOptions = {
        Transform = {
            position = "0, 0, 200",
            rotation = " 0 ,0 ,0 ",
            scale = " 1.000000 ,1.000000 ,1.000000 ",
        },
        Enabled = "true",
        Focus = {
            overlayName = "FocusElementOptions",
            imageName = "SelectorFoco"
        }
    },
    audio = {
        AudioSource = {
            path = "./assets/sounds/samba_UCM.ogg",
            type = "1",
            volume = "1",
            loopable = "true",
            playOnStart = "true"
        }
    }
}

function popScene()
    local sceneMan = SceneManager.getSceneMan();
    sceneMan:popScene("testMenu");
end

function setMasterVolume(volume)
    local audioMan = AudioManager.getAudioMan();
    audioMan:setMasterVolume(volume);
end

options_entities = {"sliderVolume", "popSceneButton", "audio", "focusOptions"}