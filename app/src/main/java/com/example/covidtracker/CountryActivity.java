package com.example.covidtracker;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.app.Dialog;
import android.app.ProgressDialog;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;
import android.widget.Toast;

import com.example.covidtracker.api.ApiUtilities;
import com.example.covidtracker.api.CountryData;

import java.util.ArrayList;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class CountryActivity extends AppCompatActivity {
    private RecyclerView recyclerView;
    private List<CountryData> list;
    private ProgressDialog dialog;
    private EditText searchbar;
    private CountryAdapter Adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.activity_country);


        recyclerView=findViewById ( R.id.countries );
        list=new ArrayList<> ();
        searchbar=findViewById ( R.id.searchbar );

        recyclerView.setLayoutManager ( new LinearLayoutManager ( this ) );
        recyclerView.setHasFixedSize (true);

        Adapter=new CountryAdapter ( this,list );
        recyclerView.setAdapter ( Adapter );


        dialog=new ProgressDialog ( this );
        dialog.setMessage ( "LOADING" );
        dialog.setCancelable ( false );
        dialog.show ();

        ApiUtilities.getApiInterface ().getCountryData ().enqueue ( new Callback<List<CountryData>> () {
            @Override
            public void onResponse(Call<List<CountryData>> call, Response<List<CountryData>> response) {
                list.addAll ( response.body () );
                Adapter.notifyDataSetChanged ();
                dialog.dismiss ();

            }

            @Override
            public void onFailure(Call<List<CountryData>> call, Throwable t) {
                dialog.dismiss ();
                Toast.makeText (CountryActivity.this,"Error"+t.getMessage (),Toast.LENGTH_SHORT).show ();
            }
        } );

        searchbar.addTextChangedListener ( new TextWatcher () {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                filter(s.toString ());

            }
        } );
    }

    private void filter(String text) {
        List<CountryData> filterlist=new ArrayList<> ();
        for(CountryData item : list)
        {
            if(item.getCountry ().toLowerCase ().contains ( text.toLowerCase () ))
            {
                filterlist.add ( item );
            }
        }
        Adapter.filterList ( filterlist );
    }
}