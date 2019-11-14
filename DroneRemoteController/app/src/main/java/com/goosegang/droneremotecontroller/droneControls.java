package com.goosegang.droneremotecontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.Button;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;


public class droneControls extends AppCompatActivity {

    Button btnFwd, btnBwd, btnRight, btnLeft, btnUp, btnDown;
    BluetoothAdapter myBluetoothAdapter;
    BluetoothSocket mySocket;
    BluetoothDevice myDevice;
    OutputStream myOutputStream;
    InputStream myInputStream;
    Set<BluetoothDevice> pairedDevices;
    public static String EXTRA_ADDRESS = "device_address";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_drone_controls);

        btnFwd = (Button)findViewById(R.id.buttonFwd);
        btnRight = (Button)findViewById(R.id.buttonRight);
        btnLeft = (Button)findViewById(R.id.buttonLeft);
        btnBwd = (Button)findViewById(R.id.buttonBwd);
        btnUp = (Button)findViewById(R.id.buttonUp);
        btnDown = (Button)findViewById(R.id.buttonDown);


        try {
            findBT();
            openBT();



            btnFwd.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                    System.out.println("fwd");

                    try {
                        sendFwd();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

            btnRight.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    System.out.println("right");

                    try {
                        sendRight();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

            btnLeft.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    System.out.println("left");

                    try {
                        sendLeft();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

            btnBwd.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    System.out.println("bwd");

                    try {
                        sendBwd();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

            btnUp.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    System.out.println("up");

                    try {
                        sendUp();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

            btnDown.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    System.out.println("down");

                    try {
                        sendDown();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

        } catch (IOException e) {

        }

    }

    void findBT (){

        myBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        if (myBluetoothAdapter == null)  {
            //btProblems.setText("This device is not bluetooth capable.");
            Toast.makeText(getApplicationContext(), "This device is not bluetooth capable.", Toast.LENGTH_LONG).show();

            finish();
        }else{
            Toast.makeText(getApplicationContext(), "Bluetooth works", Toast.LENGTH_LONG).show();
        }

        if(!myBluetoothAdapter.isEnabled()) {
            //btProblems.setText("Bluetooth is not on.");
            Toast.makeText(getApplicationContext(), "Bluetooth is not on.", Toast.LENGTH_LONG).show();
            finish();
        }else{
            Toast.makeText(getApplicationContext(), "Bluetooth is on", Toast.LENGTH_LONG).show();
        }

        pairedDevices = myBluetoothAdapter.getBondedDevices();

        if (pairedDevices.size() > 0 ) {

            for (BluetoothDevice device : pairedDevices) {
                Log.d("devices", device.getName());
                if (device.getName().equals("HC-05")) {
                    myDevice = device;
                    break;
                }
            }
        }

        //btProblems.setText("HC-05 found.");
        if (myDevice.getName().equals("HC-05")){
            Toast.makeText(getApplicationContext(), "HC-05 found.", Toast.LENGTH_LONG).show();
        }

        else if (!myDevice.getName().equals("HC-05")) {
            //btProblems.setText("HC-05 not found.");
            Toast.makeText(getApplicationContext(), "HC-05 not found.", Toast.LENGTH_LONG).show();
            finish();
        }


    }

    void openBT() throws IOException {

        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); //Standard SerialPortService ID
        mySocket = myDevice.createRfcommSocketToServiceRecord(uuid);
        mySocket.connect();
        myOutputStream = mySocket.getOutputStream();
        myInputStream = mySocket.getInputStream();
        Toast.makeText(getApplicationContext(), "Bluetooth Opened", Toast.LENGTH_LONG).show();

        //btProblems.setText("Bluetooth Opened");
    }

    void sendFwd() throws IOException {
        myOutputStream.write("1".toString().getBytes());
    }

    void sendRight() throws IOException {
        myOutputStream.write("2".toString().getBytes());
    }

    void sendLeft() throws IOException {
        myOutputStream.write("3".toString().getBytes());
    }

    void sendBwd() throws IOException {
        myOutputStream.write("4".toString().getBytes());
    }

    void sendUp() throws IOException {
        myOutputStream.write("5".toString().getBytes());
    }

    void sendDown() throws IOException {
        myOutputStream.write("6".toString().getBytes());
    }
}
