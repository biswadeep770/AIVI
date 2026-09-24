import asyncio
import os
import serial

from google import genai
from google.genai import types

COM_PORT = "COM12"
BAUD_RATE = 921600

# Put your Gemini API key in the GEMINI_API_KEY
# environment variable before running this program.
client = genai.Client(api_key=os.environ["GEMINI_API_KEY"])

MODEL = "gemini-3.5-transcribe-live"


async def main():

    ser = serial.Serial(
        COM_PORT,
        BAUD_RATE,
        timeout=1
    )

    print("Connected to ESP32 on", COM_PORT)
    print("Connecting to Gemini...")
    
    config = types.LiveConnectConfig(
        response_modalities=["TEXT"],
        input_audio_transcription=types.AudioTranscriptionConfig(),
    )

    async with client.aio.live.connect(
        model=MODEL,
        config=config
    ) as session:

        print("Gemini connected.")
        print()
        print("🎤 SPEAK INTO THE INMP441")
        print("Press Ctrl+C to stop.")
        print()

        async def send_audio():

            while True:

                # Approximately 100 ms of 16-bit mono PCM
                chunk = ser.read(3200)

                if chunk:
                    await session.send_realtime_input(
                        audio=types.Blob(
                            data=chunk,
                            mime_type="audio/pcm;rate=16000"
                        )
                    )

        async def receive_transcription():

            async for response in session.receive():

                content = response.server_content

                if not content:
                    continue

                if content.input_transcription:
                    text = content.input_transcription.text

                    if text:
                        print("YOU:", text)

        await asyncio.gather(
            send_audio(),
            receive_transcription()
        )


if __name__ == "__main__":
    asyncio.run(main())