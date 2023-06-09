package com.example.roomapp;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import com.google.android.material.slider.Slider;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

@SuppressLint("MissingPermission")
public class ControllerActivity extends AppCompatActivity {

    private OutputStream bluetoothOutputStream;
    private Slider slider;
    private Button onButton;
    private Button offButton;
    private BluetoothClientConnectionThread connectionThread;


    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controller);
        initUI();
    }

    private void initUI() {
        slider = findViewById(R.id.discreteSlider);
        slider.setEnabled(false);
        onButton = findViewById(R.id.onButton);
        offButton = findViewById(R.id.offButton);
        onButton.setBackgroundColor(Color.LTGRAY);
        offButton.setBackgroundColor(Color.LTGRAY);
        onButton.setEnabled(true);
        offButton.setEnabled(true);
        onButton.setOnClickListener((v) -> sendLightMessage(true));
        offButton.setOnClickListener((v) -> sendLightMessage(false));
        slider.addOnSliderTouchListener(new Slider.OnSliderTouchListener() {
            @SuppressLint("RestrictedApi")
            @Override
            public void onStartTrackingTouch(@NonNull Slider slider) {
            }

            @SuppressLint("RestrictedApi")
            @Override
            public void onStopTrackingTouch(@NonNull Slider slider) {
                new Thread(() -> {
                    try {
                        Integer value = Math.round(slider.getValue());
                        String message = "{\"RollerBlinds\":" + Integer.toString(Math.round(slider.getValue())) + "}\n";
                        Log.e(C.TAG, message);
                        bluetoothOutputStream.write(message.getBytes(StandardCharsets.UTF_8));
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }).start();
            }
        });
    }

    private void sendLightMessage(boolean ledState) {
        new Thread(() -> {
            try {
                String message = "{\"Lights\":" + ledState + "}\n";
                Log.e(C.TAG, message);
                bluetoothOutputStream.write(message.getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
    }

    @Override
    protected void onStart() {
        super.onStart();
        Intent intent = getIntent();
        BluetoothDevice bluetoothDevice = intent.getParcelableExtra(ScanActivity.X_BLUETOOTH_DEVICE_EXTRA);
        BluetoothAdapter btAdapter = getSystemService(BluetoothManager.class).getAdapter();
        Log.i(C.TAG, "Connecting to " + bluetoothDevice.getName());
        connectionThread = new BluetoothClientConnectionThread(bluetoothDevice, btAdapter, this::manageConnectedSocket);
        connectionThread.start();
    }

    private void manageConnectedSocket(BluetoothSocket socket) {
        try {
            bluetoothOutputStream = socket.getOutputStream();
            Log.i(C.TAG, "Connection successful!");
        } catch (IOException e) {
            Log.e(C.TAG, "Error occurred when creating output stream", e);
        }
        runOnUiThread(() -> {
            slider.setEnabled(true);
            onButton.setEnabled(true);
            offButton.setEnabled(true);
            onButton.setBackgroundColor(Color.GREEN);
            offButton.setBackgroundColor(Color.RED);
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
        connectionThread.cancel();
    }

}